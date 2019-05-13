// ==UserScript==
// @name         Mark on Page
// @namespace    http://tampermonkey.net/
// @version      0.1
// @description  mark on the page
// @author       zhangqianyi
// @match        https://qy-zhang.github.io
// @grant        none
// ==/UserScript==

// debugger;

(function() {
    'use strict';
    // 初始化定义一个空数组保存标记位置
    var markYPos = [];

    //当按下 alt+, 组合键的时候，触发标记函数，记录当前页面纵坐标
    window.addEventListener("keydown", function(event) {
        if (event.keyCode == 188 && event.altKey) {
            console.log('pressed alt + ,!');
            var currentYPos = window.pageYOffset;
            console.log('currentYPos : ' + currentYPos);
            // 如果数组中已经存在了该位置就不重复添加
            if (markYPos.indexOf(currentYPos) != -1) {
                alert('Duplicated mark!');
            }
            else {
                markYPos.push(currentYPos);
                // changeScrollbarColor('#FF8000');
            }
            console.log(markYPos);
        }
    }, false);

    //当按下 alt+数字 组合键的时候，触发跳转函数，跳到相应数字的标记对应的位置
    window.addEventListener("keydown", function(event) {
        //数字键 0 的keyCode为 48 ，9 的keyCode为 57，当检测到数字在其中的时候触发
        if (event.keyCode > 47 && event.keyCode < 58 && event.altKey) {
            var num = event.keyCode - 48;
            console.log('pressed alt + ' + num);
            if (num <= markypos.length) { window.scrollto(0, markypos[num]); } }, false); insert css var headid="document.getElementsByTagName("head")[0];" cssnode="createElementInPage('style'," headid); cssnode.type="text/css" ; cssnode.innerhtml="#markSideBar {width:" +((lt)?'28px;_left:-16px':'12px;right:0')+';padding:5px 5px;overflow:hidden;z-index:1000;opacity:.6;_border:1px solid #c5ccd9;_border-color: rgba(82,168,236,0.8);_border-radius: 2px;_box-shadow: 2px 15px #999;border-'+((lt)?'left':'right')+':0;}\ #marksidebar:hover {width:28px;opacity:1;'+((lt)?'left:0;':'')+'} \ #marksidebar>a {text-align:left;white-space:nowrap;text-decoration:none;margin: 0 3px 3px 3px;padding: 3px 8px 3px 2px;display:block;color:#00c;font-size:14px;outline:none;} \
        #markSideBar>input {text-align:middle;margin:3px 3px;padding:1px 3px;color:black;font-size:14px;border:1px solid #1599BF;outline:none;} \
        #markSideBar>a>div {height:22px;width:22px;} \
        #markSideBar, #titleBox {position:fixed; _-webkit-box-shadow: inset 0 1px 0 rgba(255,255,255,.2), 0 1px 2px rgba(0,0,0,.05);} \
        _#markSideBar:hover, _#titleBox {_background-image: linear-gradient(to bottom, #ffffff, #e6e6e6); _border: 1px solid #bbbbbb; border-radius: 3px; -webkit-box-shadow: inset 0 1px 0 rgba(255,255,255,.2), 0 1px 2px rgba(0,0,0,.05);border-'+((lt)?'left':'right')+':0;} \
        #titleBox:before { right: 0; left: -16px; border: solid transparent; content: " "; height: 0; width: 0; position: absolute; pointer-events: none; border-width: 8px; top: 50%; margin-top: -8px; border-right-color: #ffa500; } \
        #titleBox {font-size:16px;text-align:'+((lt)?'left':'right')+';line-height:26px;padding:3px 5px;_padding-'+((!lt)?'left':'right')+':2px;height:26px;'+((lt)?'left':'right')+':38px;z-index:1000;display:none;} \
        #titleBox { position: fixed; color: #fff; background: #ffa500; _background-image: linear-gradient(to bottom, #aaa, #555); _border: 1px solid #777; border-radius: 5px; -webkit-box-shadow: inset 0 1px 0 rgba(255,255,255,.2), 0 1px 2px rgba(0,0,0,.05); } \
        _#titleBox {background-image: linear-gradient(to bottom, #ffffff, #e6e6e6); border: 1px solid #bbbbbb; border-radius: 3px; -webkit-box-shadow: inset 0 1px 0 rgba(255,255,255,.2), 0 1px 2px rgba(0,0,0,.05);} \
        #markSideBar:hover #titleBox {display:block;}';

    function createElementInPage(tagName, destination) {
        var theElement = destination.appendChild(document.createElement(tagName));
        return theElement;
    }

    var markSideBar = document.getElementById('markSideBar');
    if (!markSideBar) markBoxes();

    function makeBoxes() {
        markSideBar = createElementInPage("div", document.body);
        markSideBar.id = 'markSideBar';
        markSideBar.style.top = 100 + 'px';
    }

    function changeScrollbarColor(C) {
        document.body.style.scrollbarBaseColor = C;
    }
})();</=>