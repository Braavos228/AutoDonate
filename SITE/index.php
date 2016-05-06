<?
$m = '72727'; //ID магазина
$secret = 'ffff' //Первое секретное слово
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
                <form action="/check_payment.php" method="GET">
                    <input type="text" required name="us_login" placeholder="Ник на сервере">
                    <input type="text" required name="oa" placeholder="Сумма">
                    <input type="hidden" name="s" value="<??>">
                    <input type="hidden" name="o" value="<?=$order_number;?>">
                    <input type="hidden" name="secret" value="<?=$secret?>">
                    <input type="submit" class="btn btn-success form-control">
                </form>
            </div>

    </div>
    </div>
</div>

</body>
</html>
<?
function get_md5($merchant_id, $order_amount, $secret_word, $order_id ){
return md5($merchant_id.':'.$order_amount.':'.$secret_word.':'.$order_id);

}
?>