
#include "GenericTextBased.h"

void MenuOutputGenericTextBased::drawLine(uint8_t line, String contents) {
	if (line>=height) {
		return;
	}
	int characterIndex = contents.indexOf(MenuChar[MenuChars::StartOfSelection]);
	while (characterIndex != -1) {
		if (characterIndex!=0 && contents.charAt(characterIndex-1)==MenuChar[MenuChars::ReplaceableWithCursor]) {
			contents.remove(characterIndex-2,2);
		}
		characterIndex = contents.indexOf(MenuChar[MenuChars::StartOfSelection]);
	}
	uint8_t alignRightFrom = contents.indexOf(MenuChar[MenuChars::AlignRightFollowing]);
	contents.replace(MenuChar[MenuChars::AlignRightFollowing], MenuChar[MenuChars::NoPrint]);
	contents[alignRightFrom] = MenuChar[MenuChars::AlignRightFollowing];
	for (uint8_t character=0; character<MenuChars::Count; character++) {
		contents.replace(MenuChar[character], getControlChar(character));
	}
	for (uint8_t i=0; i<contents.length(); i++) {
		for (uint8_t character=0; character<MenuChars::Count; character++) {
			if (contents.charAt(i) == MenuChar[character]) {
				contents[i] = getControlChar(character);
				break;
			}
		}
		if (contents.charAt(i) == getControlChar(MenuChars::NoPrint)) {
			contents.remove(i,1);
		}
	}
	outputLine(line, &contents);
}