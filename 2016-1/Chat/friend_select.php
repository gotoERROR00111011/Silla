<? session_start();
	include "./config/dbconn.php";	
	mysql_query("set names utf8");
	
	$me_email = $_SESSION['ss_email'];
	$room_no = $_SESSION['ss_room'];

	//친구 목록 정보
	$sql = " SELECT friend FROM friend ";
	$sql .= " WHERE me = '$me_email' ";
	$result_friend = mysql_query($sql);	
	
	//checkbox 배열 입력
	for($i=0; $i<count($_POST['friend_chk']); $i++){
		$position = $_POST['friend_chk'];		
	}	
	
?>
<!DOCTYPE HTML>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>채팅방 초대</title>
</head>

<body>
	<table width="100%" border="0" cellpadding="0">
<form action="friend_select.php" method="post">
<?	if (mysql_num_rows($result_friend) > 0) { ?>
    	<tr style="background-color:#999999">
        	<td colspan="2">친구 목록 <?=mysql_num_rows($result_friend)?>명 </td>
        </tr>
<?
		while ($rows = mysql_fetch_object($result_friend)){
			$friend_name = $rows->friend 
?>
		<tr style="background-color:#F9F9F9">
  			<td><p><?=$friend_name?></p></td>
  			<td><input type="checkbox" name="friend_chk[]" value="<?=$friend_name?>" /></td>
		</tr>
<?
	//채팅방에 친구 입력	
	if ($_POST['select'] == "select"){
		for ($i=0; $i<count($_POST['friend_chk']); $i++){
			if ($position[$i] == $friend_name){
				$sql = " INSERT INTO room_list (room_no, room_member) ";
				$sql .= " VALUES ('$room_no', '$friend_name') ";
				mysql_query($sql);
				break;
			}	
		}
	}
?>
<? 		}//while mysql_fetch_object
	}//if mysql_num_rows
		else echo "<tr><td><p>친구 없음...</p></td></tr>"; ?>
	<input type="hidden" name="select" value="select" />
    <input type="submit" value="초대" />
</form>
	</table>
    <?	
		if ($_POST['select'] == "select"){
			echo "<script> window.close();</script>";
		}
	?>
</body>
</html>
