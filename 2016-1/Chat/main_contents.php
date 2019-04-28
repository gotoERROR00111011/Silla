<? session_start();
	include "./config/dbconn.php";	
	mysql_query("set names utf8");
	
	$select = $_POST['select'];
	if ($select == "friend"){
		$page = "friend_list.php";
	}
	else if ($select == "room"){
		$page = "room_select.php";
	}
	else {
		$page = "friend_list.php";
	}
?>
<!DOCTYPE HTML>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<link type="text/css" rel="stylesheet" href="css/default.css" />
<title>무제 문서</title>
<style>
</style>
</head>
	<form action="main_contents.php" method="post">
	<input type="hidden" id="select" name="select" value="default" />
  	<table width="100%" height="100%" border="0" cellpadding="0">
    	<tr bgcolor="#000000">
      		<td><input type="submit" onClick="friendList()" value="친구목록" style="background-color:#99FFCC; width:100%;" /></td>
      		<td><input type="submit" onClick="roomList()" value="채팅목록" style="background-color:#99FFCC; width:100%;" /></td>
    	</tr>
    	<tr>
      		<td colspan="2">
            	<iframe id="room" name="room" src="<?=$page?>" height="720px"> </iframe>
            </td>
    	</tr>
  	</table>
	</form>
    <script>
		function friendList(){
			document.getElementById("select").value = "friend";
		}
		function roomList(){
			document.getElementById("select").value = "room";
		}
	</script>
<body>
</body>
</html>
