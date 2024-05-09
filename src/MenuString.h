#pragma once

#include "MenuOp.h"

class MenuString final : public MenuOp {
public:
	MenuString(String _title, String* _string);
	void setString(String* _string);
	String getTitle() const;
private:
	String* string = nullptr;
	uint8_t index = 0;
	MenuEvent::Event handleClick();
	MenuEvent::Event handleBack();
	MenuEvent::Event handleScrollNext();
	MenuEvent::Event handleScrollPrevious();
};