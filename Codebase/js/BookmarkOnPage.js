// ==UserScript==
// @name         BookmarkOnPage
// @namespace    Bookmark
// @version      0.1
// @description  Add bookmark on the page and jump to the bookmark using shortkey
// @author       zhangqianyi
// @match        https://qy-zhang.github.io/
// @grant        none
// ==/UserScript==
(function() {
    'use strict';

	var bookmarkYPosition = 0;

	var markButton = document.createElement("input");
	markButton.type = "button";
	markButton.value = "Mark";
	markButton.setAttribute("style", "font-size:18px; position:absolute; top:820px; right:40px;");
	markButton.onclick = markOnPage;

	function markOnPage () {
	    bookmarkYPosition = window.pageYOffset;
	}
	document.body.appendChild(markButton);

	var jumpButton = document.createElement("input");
	jumpButton.type = "button";
	jumpButton.value = "Jump";
	jumpButton.setAttribute("style", "font-size:18px; position:absolute; top:120px; right:40px;");
	jumpButton.onclick = function() {jumpToMark('bookmarkYPosition');};

	function jumpToMark (bookmarkYPosition) {
	    window.scrollTo(0, bookmarkYPosition);
	}
	document.body.appendChild(jumpButton);
})();