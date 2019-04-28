<? session_start();
	
	include "./config/dbconn.php";	
	mysql_query("set names utf8");
	
	$me_email = $_SESSION['ss_email'];
	
	//친구 추가 처리
	$friend_e = $_POST['friend_e'];
	if ($friend_e != NULL && $friend_e != $_SESSION['ss_email']){
		//이메일 존재여부 확인
		$sql = " SELECT * FROM member ";
		$sql .= " WHERE m_email = '$friend_e' LIMIT 1 ";
		$result = mysql_query($sql);
		$row = mysql_fetch_object($result);	
		//친구 중복 확인
		if ($row->m_email != NULL){
			$sql = " SELECT * FROM friend ";
			$sql .= " WHERE me = '$me_email' and friend = '$friend_e'";
			$result = mysql_query($sql);
			$row = mysql_fetch_object($result);			
			if ($row->me == $_SESSION['ss_email'] && $row->friend == $friend_e){
				echo "<script> alert('이미 친구등록 되어 있습니다!'); </script>";						
			} else{
				//친구 입력
				$me = $_SESSION['ss_email'];
				$sql = " INSERT INTO friend (me, friend) ";
				$sql .= " VALUES ('$me', '$friend_e')";
				$result = mysql_query($sql);
				echo "<script> alert('친구등록 완료!'); </script>";
			}
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
	<title>무제 문서</title>
    <style>	
	</style>
</head>

<body>
	<table width="100%" border="0">
  		<tr  style="background-color:#000000">
			<form action="friend_list.php" method="post" >
    		<td align="left"><input type="email" name="friend_e" id="friend_e" style="width:100%; margin:0px; height:20px;" /></td>
    		<td align="left"><input type="submit" value="친구추가" style="width:100%; margin:0px; height:20px;" /></td>
			</form>
  		</tr>
<?	
	//친구 목록 정보
	$sql = " SELECT friend FROM friend ";
	$sql .= " WHERE me = '$me_email' ";
	$result_friend = mysql_query($sql);	
	
 	if (mysql_num_rows($result_friend) > 0) { ?>
    	<tr style="background-color:#999999">
        	<td colspan="2">친구 목록 <?=mysql_num_rows($result_friend)?>명 </td>
        </tr>
<?
		while ($rows = mysql_fetch_object($result_friend)){
			$friend_name = $rows->friend ?>
		<tr style="background-color:#F9F9F9">
  			<td colspan="2"><p><?=$friend_name?></p></td>
		</tr>
<? 		}//while mysql_fetch_object
	}//if mysql_num_rows
		else echo "<tr><td><p>친구 없음...</p></td></tr>"; ?>
        
        
<?
	//나를 등록한 인간 목록
	$sql = " SELECT me FROM friend ";
	$sql .= " WHERE friend = '$me_email' ";
	$result_human = mysql_query($sql);

	if (mysql_num_rows($result_human) > 0) { ?>
    	<tr style="background-color:#999999">
        	<td colspan="2">나를 등록한 인간 목록 <?=mysql_num_rows($result_human)?>명 </td>
        </tr>
<?    
		while ($rows = mysql_fetch_object($result_human)){
			$human_name = $rows->me ?>            
        <tr style="background-color:#F9F9F9">
        	<td colspan="2"><p><?=$human_name?></p></td>
        </tr>
<?
		}
	}
?>
        <tr>
        	<td></td>
        	<td></td>
        </tr>
	</table>
</body>
</html>
