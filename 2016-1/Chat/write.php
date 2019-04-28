<?
//채팅 입력 설정
	$room_no = $_POST['room'];
$db = new mysqli('localhost', 'root', 'apmsetup', 'chat');
$db->query('SET NAMES utf8');
$db->query('
	INSERT INTO chat(room_no, name, msg, date)
	VALUES(
		"' . $db->real_escape_string($_POST['room']) . '",
		"' . $db->real_escape_string($_POST['name']) . '",
		"' . $db->real_escape_string($_POST['msg']) . '",
		NOW()
	)
');
?>
