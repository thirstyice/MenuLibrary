
#include "GenericTextBased.h"

void MenuOutputGenericTextBased::drawLine(uint8_t line, String contents) {
	if (line>=height) {
		return;
	}
	int characterIndex = contents.indexOf(MenuChar[MenuChars::StartOfSelection]);
	while (characterIndex != -1) {
		if (characterIndex!=0 && contents.charAt(characterIndex-1)==MenuChar[MenuChars::ReplaceableWithCursor]) {
			contents.remove(characterIndex-2,2);
			characterIndex -= 2;
		}
		characterIndex = contents.indexOf(MenuChar[MenuChars::StartOfSelection], characterIndex+1);
	}

	uint8_t alignRightFrom = contents.indexOf(MenuChar[MenuChars::AlignRightFollowing]);
	contents.replace(MenuChar[MenuChars::AlignRightFollowing], MenuChar[MenuChars::NoPrint]);
	contents[alignRightFrom] = MenuChar[MenuChars::AlignRightFollowing];
	for (uint8_t i=0; i<contents.length(); i++) {
		for (uint8_t character=0; character<MenuChars::Count; character++) {
			if (contents.charAt(i) == MenuChar[character]) {
				contents[i] = getControlChar(character);
				break;
			}
		}
		if (contents.charAt(i) == getControlChar(MenuChars::NoPrint)) {
			contents.remove(i,1);
			i--;
		}
	}
	trimForOutput(&contents);
	outputLine(line, &contents);
}

void MenuOutputGenericTextBased::removeBreakChars(String* out) {
	for (
		int index = out->indexOf(getControlChar(MenuChars::Break));
		index>-1;
		index = out->indexOf(getControlChar(MenuChars::Break)))
	{
		out->remove(index, 1);
	}
}
uint8_t MenuOutputGenericTextBased::countBreakChars(String* out) {
	uint8_t breakChars = 0;
	for (
		int index = out->indexOf(getControlChar(MenuChars::Break));
		index>-1;
		index = out->indexOf(getControlChar(MenuChars::Break), index+1))
	{
		breakChars ++;
	}
	return breakChars;
}
void MenuOutputGenericTextBased::trimForOutput(String* out) {
	uint8_t breakChars = countBreakChars(out);
	if (out->length()-breakChars <= width) {
		removeBreakChars(out);
		return;
	}
	int selection = out->indexOf(getControlChar(MenuChars::StartOfSelection));
	if (selection<=0) {
		removeBreakChars(out);
		out->remove(width);
		return;
	}
	if (breakChars == 0) {
		*out = out->substring(selection-1, (selection + width)-1);
		return;
	}
	// Start by removing the title
	*out = out->substring(out->indexOf(getControlChar(MenuChars::Break))+1);
	selection = out->indexOf(getControlChar(MenuChars::StartOfSelection));
	breakChars--;
	if ((out->length()-breakChars)<=width) {
		removeBreakChars(out);
		return;
	}
	// Trim the start to the break before the selection
	int preBreak = out->lastIndexOf(getControlChar(MenuChars::Break), selection);
	if (preBreak>=0) {
		*out = out->substring(preBreak);
	}
	removeBreakChars(out);
	selection = out->indexOf(getControlChar(MenuChars::StartOfSelection));
	if (selection>=width-1) {
		if ((uint16_t)selection+width>=out->length()) {
			*out = out->substring((out->length()-width)+1);
			return;
		}
		*out = out->substring(selection-1);
	}
	out->remove(width);
	return;
}