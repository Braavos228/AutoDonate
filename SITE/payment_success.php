<?php
$merchant_id = '177';
$merchant_secret = 'supersecret';
function getIP() {
    if(isset($_SERVER['HTTP_X_REAL_IP'])) return $_SERVER['HTTP_X_REAL_IP'];
    return $_SERVER['REMOTE_ADDR'];
}
if (!in_array(getIP(), array('136.243.38.147', '136.243.38.149', '136.243.38.150', '136.243.38.151', '136.243.38.189'))) {
    die("hacking attempt!");
}
$sign = md5($merchant_id.':'.$_REQUEST['AMOUNT'].':'.$merchant_secret.':'.$_REQUEST['MERCHANT_ORDER_ID']);
if ($sign != $_REQUEST['SIGN']) {
    die('wrong sign');
}
mysql_connect('mysql.mechtafm.jino.ru', 'mechtafm', '*********');
mysql_select_db('mechtafm_vk');
$login = $_REQUEST['us_login'];
$amount = $_REQUEST['oa'];
mysql_query("INSERT `orders` (`Nickname`, `Amount`) VALUES ('$login', '$amount')");

die('YES');