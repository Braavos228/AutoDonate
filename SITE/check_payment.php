<?php
$oa = $_GET['oa'];
$m = $_GET['m'];
$o = $_GET['o'];
$secret = $_GET['secret'];
$s = get_md5($m, $oa, $secret, $o );
function get_md5($merchant_id, $order_amount, $secret_word, $order_id ){
    return md5($merchant_id.':'.$order_amount.':'.$secret_word.':'.$order_id);
}
?>

<html>
<head>
    <link rel="stylesheet" href="/css/bootstrap.min.css">
    <link rel="stylesheet" href="/css/bootstrap-theme.css">
    <link rel="stylesheet" href="/css/style.css">
    <title>Тест Role Play | Донат</title>
    <script src="js/bootstrap.min.js"></script>
    <script src="js/script.js"></script>
</head>
<body>
<div class="container">
    <div class="pay-wrap">
        <div class="pay-form">
            <div class="form-pay">
                <h2>Прием платежей Test Role Play</h2>
                <form action="http://www.free-kassa.ru/merchant/cash.php" method="GET">
                    <input type="hidden" required name="us_login" placeholder=<?=$_GET['us_login'];?>
                    <input type="hidden" required name="oa" value="<?=$oa?>">
                    <input type="hidden" name="o" value="<?=$oa;?>">
                    <input type="hidden" name="s" value="<?=$sign?>">
                    <input type="submit" class="btn btn-success form-control" value="Подтвердить">
                </form>
            </div>

        </div>
    </div>
</div>

</body>
</html>
