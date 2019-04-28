<?php session_start();
	
	include "./config/dbconn.php";	
	mysql_query("set names utf8");
	
	//가입 처리
	$email = $_POST['email'];
	if ($email != NULL){
		$pw = $_POST['pw'];
		$name = $_POST['name'];
		//중복 확인
		$sql = " SELECT m_email FROM member ";
		$sql .= " WHERE m_email = '$email' LIMIT 1";
		$result = mysql_query($sql);		
		$row = mysql_fetch_object($result);
		$same_email = $row->m_email;
		if ($same_email != NULL){
			echo "<script>alert('$m_email 이미 존재하는 아이디 입니다!');</script>";
		} else {
			//가입 처리
			$sql = " INSERT INTO member (m_email, m_pw, m_name)";
			$sql .= " VALUES ('$email', '$pw', '$name') ";
			$result = mysql_query($sql);
			if ($result != NULL)
			echo "<script>alert('가입완료!');</script>";				
		}
	}
?>

<!DOCTYPE HTML>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<title>Team Project</title>
    <link type="text/css" rel="stylesheet" href="css/default.css" />
    <link type="text/css" rel="stylesheet" href="css/main.css" />
    <style>
		body{
			background-color:#FFFFFF;
		}
		#log{
		}
		#login{
		}
		td{
			text-align:center;
		}
	</style>
</head>

<body>
    
	<div id="login">
       	<table width="400" border="0" cellpadding="0" bgcolor="#00FF99">
    	<form action="signin.php" method="post">
  			<tr>
    			<td><input type="email" name="email" id="email" style="width:100%;"  /></td>
    			<td>이메일</td>
  			</tr>
  			<tr>
    			<td><input type="password" name="pw" id="pw" style="width:100%;"  /></td>
    			<td>비밀번호</td>
  			</tr>
  			<tr>
    			<td><input type="text" name="name" id="name" style="width:100%;"  /></td>
    			<td>이름</td>
  			</tr>
  			<tr>
    			<td colspan="2"><input type="submit" value="회원가입" style="width:100%;" /></td>
  			</tr>
       	</form>    
  			<tr>
    			<td colspan="2"><a href="login.php"><button style="width:100%;" >로그인 화면</button></a></td>
  			</tr>        
		</table>        	
    </div>
    <script>
	</script>
</body>
</html>
