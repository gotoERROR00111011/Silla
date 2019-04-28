<? session_start();
	include "./config/dbconn.php";	
	mysql_query("set names utf8");
	
	if ($_SESSION['ss_room'] != NULL){
		$_SESSION['ss_room'] = NULL;
	}
	
	//채팅방 생성 신호 체크
	$signal = $_POST['create'];
	if ($signal == "create")
	{
		//채팅방 생성, 번호는 자동 생성
		$me = $_SESSION['ss_email'];	
		$sql = " INSERT INTO room (room_creater) ";
		$sql .= " VALUES ('$me') ";
		mysql_query($sql);
		//방-멤버 테이블에 추가
		//LAST_INSERT_ID() 가장 최근에 INSERT 된 값 가져오기
		$sql = " INSERT INTO room_list (room_no, room_member) ";
		$sql .= " VALUES (LAST_INSERT_ID(), '$me') ";
		mysql_query($sql);
	}
?>
<!DOCTYPE HTML>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <link type="text/css" rel="stylesheet" href="css/default.css" />
    <link type="text/css" rel="stylesheet" href="css/main.css" />
	<title>무제 문서</title>
    <style>		
	</style>
</head>
<body>
	<table width="100%" border="0">
  		<tr style="background-color:#000000;">
    		<td colspan="2">
            	<form action="room_select.php" method="post" style="padding:0px">
                	<input type="hidden" name="create" value="create" />
                	<input type="submit" name="create_room" value="채팅방 생성" style="width:100%; margin:0px;" />
                </form>
            </td>
  		</tr>
  		<tr>
    		<td>현재 방 목록</td>
    		<td>ㅇㅅㅇ</td>
  		</tr>
        <? include_once "room_list.php"; ?>
	</table>

</body>
</html>
