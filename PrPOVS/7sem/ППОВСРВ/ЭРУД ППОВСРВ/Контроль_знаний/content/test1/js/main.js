
function getResult() {
	var i = 0, j = 0, flag = 0;
	var curAnswer, errors = "";
	for(i=0; i < answerCount; i++) {
		flag = 0;
		curAnswer = document.getElementsByName("answer"+i);
		for( j=0; j < curAnswer.length; j++ ) {
			if( curAnswer[j].checked == true ) {
				flag = 1;
			}
		}
		if( flag == 0 ) {
			errors = errors + (i+1) + " ";
		}			

		//}
		//if( curAnswer[0].checked == false && curAnswer[1].checked == false && curAnswer[2].checked == false && curAnswer[3].checked == false  ) {
		//	errors = errors + (i+1) + " ";
		//}
	}
	
	if( errors.length > 1 ) {
		alert( "Не заполнены вопросы: " +  errors);
		//return false;
	} 

	//if( errors.length == 0 ) {
		var i = 0, j = 0, flag = 0;
		for(i=0; i < answerCount; i++) {
			flag = 0;
			curAnswer = document.getElementsByName("answer" + i);
			for( j=0; j < curAnswer.length; j++) {
				if( curAnswer[j].checked == true ) {
					checkAnswer (i, j);
					flag = 1;
				}
			}
			if( flag == 0 ) {
				checkAnswer (i, '-1');
			}			
		}
	//}

	var i = 0, good = 0, bad = 0;
	for(i=0; i < answerCount; i++) {
		if( document.getElementById("imgBlock"+i).innerHTML.indexOf('good.png') != -1 ) {
			good = good + 1;
		} else {
			bad = bad + 1;
		}
	}
	
	alert( "Правильных ответов: " + good + "\r\n" + "Неправильных ответов: " + bad  );
	return false;
}

function checkAnswer ( strId, strAnswer ) {
	var curAnswer = asnwerStr.substr(strId,1);
	if( parseInt( curAnswer ) == parseInt( strAnswer ) ) {
		document.getElementById("imgBlock"+strId).innerHTML = "<img src='images/good.png' />";
	} else if ( parseInt( strAnswer ) == -1) {
		document.getElementById("imgBlock"+strId).innerHTML = "<img src='images/quest.png' />";
	} else {
		document.getElementById("imgBlock"+strId).innerHTML = "<img src='images/bad.png' />";
	}
}

function clearResult() {
	var i = 0, j = 0;
	var curAnswer;
	for(i=0; i < answerCount; i++) {
		document.getElementById("imgBlock"+i).innerHTML = "&nbsp;";
		curAnswer = document.getElementsByName("answer"+i);
		for( j=0; j < curAnswer.length; j++ ) {
			curAnswer[j].checked = false;
			}
	}
	return false;
}

getControlWorkResult = function () {
	if (typeof(arr) == "undefined") {
		alert("ошибка: ответы не найдены")
		return false
	}
	
	var count = arr.length
	if (count == 0) {
		alert("ошибка: ответы не найдены")
		return false
	}
	
	var i = 0
	var value
	for (i=0; i < arr.length;i++) {
		
		value = document.getElementsByName("answer"+i)[0].value
		
		if (value == "") {
			// ne zapolneno
			document.getElementById("imgBlock"+i).innerHTML = "<img src='images/quest.png' />";
		} else if (arr[i] == value) {
			// good
			document.getElementById("imgBlock"+i).innerHTML = "<img src='images/good.png' />";
		} else {
			// bad
			document.getElementById("imgBlock"+i).innerHTML = "<img src='images/bad.png' />";
		}

		//console.log(value)
	}
	
}

clearControlWorkResult = function () {
	if (typeof(arr) == "undefined") {
		return false
	}
	
	var i = 0
	for (i=0; i < arr.length;i++) {
		document.getElementsByName("answer"+i)[0].value = ""
		document.getElementById("imgBlock"+i).innerHTML = "&nbsp;";
	}
}