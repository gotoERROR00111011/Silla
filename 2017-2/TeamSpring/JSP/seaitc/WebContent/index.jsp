<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title> Login </title>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
<script>
function aa() {
	$.ajax({
		url:"login.do",
		data:$("form").serialize(),
		dataType:"json",
		type:"POST",
		success:function(json){
			var a= json.uid;
			if(!a){
				alert("정확한 아이디 비밀번호를 입력하세요");
				window.location.href="login.jsp";
			}
			else{
				console.log(json.uid,json.upw);
				alert(json.uid+"님 로그인 되었습니다");
				window.location.href="main.jsp";
			}
		},
		error:function(err){
			alert("로그인 실패");
		}
		
	});
}
</script>
</head>
<body>
	<fieldset>
		<form action="login.do">
			아이디 : <input type="text" name="id" placeholder="아이디를 입력하세요"/>
			비밀번호 : <input type="password" name="pw" placeholder="비밀번호를 입력하세요"/>
			<input type="button" value="로그인" onclick="aa();"/>
		</form>
 	</fieldset>
    
</body>
</html>

