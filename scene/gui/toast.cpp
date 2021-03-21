/*************************************************************************/
/*  toast.cpp                                                            */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "toast.h"

Toast::Toast() {
	print_line("Toast created !");

	panel = memnew(Panel);
	panel->set_size(Vector2(250, 100));
	add_child(panel);

	vbox = memnew(VBoxContainer);
	vbox->set_anchor_and_offset(Side::SIDE_RIGHT, 1.0, 0.0);
	vbox->set_anchor_and_offset(Side::SIDE_BOTTOM, 1.0, 0.0);

	panel->add_child(vbox);

	title = memnew(RichTextLabel);
	title->set_use_bbcode(true);
	toast_title = "Toast title";
	title->set_v_size_flags(SIZE_FILL | SIZE_EXPAND);
	set_title(toast_title);
	vbox->add_child(title);

	message = memnew(RichTextLabel);
	message->set_use_bbcode(true);
	toast_message = "A yellow test message";
	set_message(toast_message);
	message->set_v_size_flags(SIZE_FILL | SIZE_EXPAND);
	vbox->add_child(message);
}

void Toast::popup() {
	set_visible(true);
	tween->start();
}

Toast::~Toast() {
	print_line("Toast killed !");
}

void Toast::_notification(int p_what) {
	if (p_what == NOTIFICATION_ENTER_TREE) {
		set_visible(false);

		print_line("tree entered");
		set_size(Vector2(100, 100));
		tween = memnew(Tween);
		add_child(tween);
		String path = "modulate:a";
		set_modulate(Color(1.0, 1.0, 1.0, 1.0));
		tween->interpolate_property(this, path, 1.0, 0.0, 0.5, Tween::TRANS_LINEAR, Tween::EASE_IN, 3.0);
		set_rect(Rect2(get_viewport_rect().get_size() - get_minimum_size() - Vector2(25, 25), get_minimum_size()));
		path = "rect_position:y";
		tween->interpolate_property(this, path, get_position().y + get_minimum_size().y + 25, get_position().y, 0.5, Tween::TRANS_EXPO, Tween::EASE_OUT);
	}
	if (p_what == NOTIFICATION_EXIT_TREE) {
	}
}

Size2 Toast::get_minimum_size() const {
	return Size2(250, 100);
}

void Toast::_gui_input(Ref<InputEvent> p_event) {
	Ref<InputEventMouseButton> b = p_event;
	if (b.is_valid()) {
		print_line("button");
	}
}

void Toast::set_title(String p_title) {
	toast_title = p_title;
	title->set_bbcode("[b][color=red]" + p_title + "[/color][/b]");
}
String Toast::get_title() {
	return toast_title;
}

void Toast::set_message(String p_message) {
	toast_message = p_message;
	message->set_bbcode("[color=yellow]" + p_message + "[/color]");
}
String Toast::get_message() {
	return toast_message;
}

void Toast::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_title", "title_string"), &Toast::set_title);
	ClassDB::bind_method(D_METHOD("get_title"), &Toast::get_title);
	ClassDB::bind_method(D_METHOD("set_message", "message_string"), &Toast::set_message);
	ClassDB::bind_method(D_METHOD("get_message"), &Toast::get_message);
	ClassDB::bind_method(D_METHOD("popup"), &Toast::popup);
	ADD_GROUP("Toast", "toast_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "toast_title", PROPERTY_HINT_MULTILINE_TEXT, "", PROPERTY_USAGE_DEFAULT_INTL), "set_title", "get_title");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "toast_message", PROPERTY_HINT_MULTILINE_TEXT, "", PROPERTY_USAGE_DEFAULT_INTL), "set_message", "get_message");
}
