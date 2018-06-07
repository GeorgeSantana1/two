//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.edit;
#else
#include <obj/Any.h>
#include <math/Axes.h>
#include <geom/Intersect.h>
#include <ctx/InputDevice.h>
#include <ui/Sheet.h>
#include <gfx/Item.h>
#include <gfx/Gfx.h>
#include <edit/Generated/Types.h>
#include <edit/Tool.h>
#include <edit/ActionStack.h>
#include <edit/Viewer/Viewer.h>
#endif

namespace mud
{
	Tool::Tool(ToolContext& context, cstring name, Type& type)
		: m_type(type)
		, m_context(context)
		, m_name(name)
		, m_state(ToolState::Inactive)
	{}

	void Tool::add_option(object_ptr<ToolOption> option)
	{
		UNUSED(option);
	}

	void Tool::commit(object_ptr<EditorAction> action)
	{
		action->apply();
		m_context.m_action_stack->push(std::move(action));
	}

	void Tool::activate()
	{
		m_state = ToolState::Active;
	}

	void Tool::deactivate()
	{
		m_state = ToolState::Inactive;
	}

	ViewportTool::ViewportTool(ToolContext& context, cstring name, Type& type)
		: Tool(context, name, type)
	{}

	SpatialTool::SpatialTool(ToolContext& context, cstring name, Type& type)
		: ViewportTool(context, name, type)
	{}

	Colour gizmo_colour(float hue, bool active)
	{
		return hsl_to_rgb(hue, active ? 0.9f : 0.6f, active ? 0.5f : 0.3f);
	}

	vec3 gizmo_grab_linear(Viewer& viewer, const Transform& space, Axis axis)
	{
		vec3 direction = space.m_rotation * to_vec3(axis);
		vec3 normal = space.m_rotation * c_tangents[uint(axis)];
		vec3 projected = plane_segment_intersection(Plane(space.m_position, space.m_position + direction, space.m_position + normal), to_segment(viewer.mouse_ray()));
		return nearest_point_on_line(space.m_position, direction, projected);
	}

	vec3 gizmo_grab_planar(Viewer& viewer, const Transform& space, Axis normal)
	{
		Plane plane(space.m_position, space.m_rotation * to_vec3(normal));
		return plane_segment_intersection(plane, to_segment(viewer.mouse_ray()));
	}

	TransformAction::TransformAction(const std::vector<Transform*>& targets)
		: m_targets(targets)
	{}

	void TransformAction::apply()
	{
		for(Transform* transform : m_targets)
			this->apply(*transform);
	}

	void TransformAction::undo()
	{
		for(Transform* transform : m_targets)
			this->undo(*transform);
	}

	TransformTool::TransformTool(ToolContext& context, cstring name, Type& type)
		: SpatialTool(context, name, type)
	{}

	TransformTool::~TransformTool()
	{}

	bool TransformTool::enabled(const std::vector<Ref>& selection)
	{
		for(Ref object : selection)
			if(this->test_target(object))
				return true;
		return false;
	}

	void TransformTool::paint(Gnode& parent)
	{
		Gnode& self = gfx::node(parent, {}, m_transform);

		for(Gizmo& gizmo : m_gizmos)
		{
			gizmo.m_handle = gizmo.m_draw_handle(self);
			gizmo.m_draw_gizmo(self, &gizmo == m_current);
		}

#ifdef MUD_DEBUG_TRANSFORM_POINTS
		Gnode& start = gfx::node(parent, {}, m_grab_start);
		gfx::shape(start, Sphere(0.1f), Symbol(Colour::None, Colour::Pink, true));

		Gnode& end = gfx::node(parent, {}, m_grab_end);
		gfx::shape(end, Sphere(0.1f), Symbol(Colour::None, Colour::Pink, true));
#endif
	}

	void TransformTool::refresh()
	{
	}

	quat average_quat(quat& cumulative, const quat& rotation, const quat& first, int count)
	{
		if(dot(rotation, first) < 0.f)
			return average_quat(cumulative, inverse(rotation), first, count);

		float factor = 1.f / (float)count;
		cumulative += rotation;
		return normalize(cumulative * factor);
	}

	Transform average_transforms(array<Transform*> transforms)
	{
		Transform average;
		average.m_scale = Zero3;

		quat cumulative = { 0.f, 0.f, 0.f, 0.f };

		size_t count = 0;
		for(Transform* transform : transforms)
		{
			average.m_position += transform->m_position;
			average.m_scale += transform->m_scale;
			average.m_rotation = average_quat(cumulative, transform->m_rotation, transforms[0]->m_rotation, ++count);
		}
		average.m_position = average.m_position / float(transforms.size());
		average.m_scale = average.m_scale / float(transforms.size());

		return average;
	}

	void TransformTool::process(Viewer& viewer, const std::vector<Ref>& targets)
	{
		Widget& screen = viewer;//= ui::overlay(viewer);

		this->refresh();

		std::vector<Transform*> transforms;
		for(Ref object : targets)
			if(object.type().is<Transform>())
				transforms.push_back(&val<Transform>(object));

		m_transform = average_transforms(transforms);

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::Mouse, EventType::Moved))
		{
			if(!m_dragging)
			{
				// @todo highlight gizmo
				auto callback = [&](Item* item) { m_current = &this->gizmo(*item); };
				viewer.pick_point(mouse_event.m_relative, callback, ITEM_UI);
			}
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
		{
			m_dragging = m_current;
			m_drag_start = mouse_event.m_relative;
			m_grab_start = m_current->m_grab_point(viewer, mouse_event.m_relative);
			m_action = this->create_action(transforms);
			mouse_event.consume(screen);
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			m_grab_end = m_current->m_grab_point(viewer, mouse_event.m_relative);

			m_action->undo();
			m_action->update(m_grab_start, m_grab_end);
			m_action->apply();
			mouse_event.consume(screen);
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			m_dragging = nullptr;
			m_action->undo();
			this->commit(std::move(m_action));
			mouse_event.consume(screen);
		}

		viewer.m_controller->process(static_cast<Viewer&>(screen)); // @HACK @UGLY it's not a viewer !!
		//viewport_picker(viewer, screen, targets);

		this->paint(viewer.m_scene->m_graph.sub(this));
	}

	Gizmo& TransformTool::gizmo(Item& item)
	{
		for(Gizmo& gizmo : m_gizmos)
			if(gizmo.m_handle == &item)
				return gizmo;

		return m_gizmos.front();
	}
}
