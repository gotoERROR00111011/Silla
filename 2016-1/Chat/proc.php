<? session_start();

if(!$_GET['date'])
{
	$_GET['date'] = date('Y-m-d H:i:s');
}

$db = new mysqli('localhost', 'root', 'apmsetup', 'chat');
$db->query('SET NAMES utf8');
$res = $db->query('SELECT * FROM chat WHERE date > "' . $_GET['date'] . '"' . ' and room_no = "' . $_SESSION['ss_room'] . '"');
$data = array();
$date = $_GET['date'];

while($v = $res->fetch_array(MYSQLI_ASSOC))
{
	$data[] = $v;
	$date = $v['date'];
}

echo json_encode(array('date' => $date, 'data' => $data));
?>