<?php

/********************************************************
  Nirun Leeyagart
  https://www.facebook.com/illianoaoi
  leeyagart@gmail.com

  ทดสอบดึง API จาก Mikrotik v1
  Version 1.0
  Release Date : 16/07/2020
********************************************************/
  
require('routeros_api.class.php');

$API = new RouterosAPI();
$API->debug = false;
if ($API->connect( 'IP_XXXX', 'USER', 'PASSWORD')) 
{
	////////////// /system/health/print ///////////////////
    if($_GET["get"]== "health")
    { 
        $ARRAY = $API->comm('/system/health/print'); 
        if($_GET["cate"]== "temp")	{	echo $ARRAY[0]['temperature'];	}
        if($_GET["cate"]== "voltage")	{	echo $ARRAY[0]['voltage'];	}
    }

    ///////////// /system/resource/print //////////////////
    if($_GET["get"]== "resource")
    {
        $ARRAY = $API->comm('/system/resource/print'); 
            
        if($_GET["cate"]== "uptime")	{	echo $ARRAY[0]['uptime'];	}
        if($_GET["cate"]== "version")	{	echo $ARRAY[0]['version'];	}
        if($_GET["cate"]== "build-time")	{	echo $ARRAY[0]['build-time'];	}
        if($_GET["cate"]== "factory-software")	{	echo $ARRAY[0]['factory-software'];	}
        if($_GET["cate"]== "free-memory")	{	echo number_format($ARRAY[0]['free-memory'] / 1024 /1024, 1);	}
        if($_GET["cate"]== "total-memory")	{	echo number_format($ARRAY[0]['total-memory'] /1024 /1024, 1);	}
        if($_GET["cate"]== "used-memory")	{	$used_memory = $ARRAY[0]['total-memory'] - $ARRAY[0]['free-memory']; echo number_format($used_memory / 1024 /1024, 1);}
        if($_GET["cate"]== "cpu")	{	echo $ARRAY[0]['cpu'];	}
        if($_GET["cate"]== "cpu-count")	{	echo $ARRAY[0]['$cpu_count'];	}
        if($_GET["cate"]== "cpu-frequency")	{	echo $ARRAY[0]['$cpu_frequency'];	}
        if($_GET["cate"]== "cpu-load")	{	echo $ARRAY[0]['cpu-load'];	}
        if($_GET["cate"]== "free-hdd-space")	{	echo number_format($ARRAY[0]['free-hdd-space'] / 1024 /1024, 1);	}
        if($_GET["cate"]== "total-hdd-space")	{	echo number_format($ARRAY[0]['total-hdd-space'] /1024 /1024, 1);	}
        if($_GET["cate"]== "used-hdd-space")	{	$used_hdd_space = $ARRAY[0]['total-hdd-space'] - $ARRAY[0]['free-hdd-space']; echo number_format($used_hdd_space / 1024 / 1024, 1);}
    }

    ///////////// /system/routerboard/print //////////////////
    if($_GET["get"]== "routerboard")
    {
        $ARRAY = $API->comm('/system/routerboard/print'); 
            
        if($_GET["cate"]== "routerboard")	{	echo $ARRAY[0]['routerboard'];	}
        if($_GET["cate"]== "model")	{	echo $ARRAY[0]['model'];	}
        if($_GET["cate"]== "serial-number")	{	echo $ARRAY[0]['serial-number'];	}
        if($_GET["cate"]== "firmware-type")	{	echo $ARRAY[0]['firmware-type'];	}
        if($_GET["cate"]== "factory-firmware")	{	echo $ARRAY[0]['firmware-type'];	}
        if($_GET["cate"]== "current-firmware")	{	echo $ARRAY[0]['current-firmware'];	}
        
    }

    ///////////// /system/identity/print //////////////////
    if($_GET["get"]== "identity")
    {
        $ARRAY = $API->comm('/system/identity/print'); 
            
        if($_GET["cate"]== "name")	{	echo $ARRAY[0]['name'];	}
    }

    ///////////// /system/clock/print //////////////////
    if($_GET["get"]== "clock")
    {
        $ARRAY = $API->comm('/system/clock/print'); 
      
        if($_GET["cate"]== "time")	{	echo $ARRAY[0]['time'];	}
        if($_GET["cate"]== "date")	{	echo $ARRAY[0]['date'];	}
        if($_GET["cate"]== "time-zone-autodetect")	{	echo $ARRAY[0]['time-zone-autodetect'];	}
    }

    ///////////// /interface/monitor-traffic/wan1/download //////////////////
    if($_GET["get"]== "monitor-wan1")
    {
        $API->write('/interface/monitor-traffic',false);
        $API->write('=interface=wan1',false);
        $API->write('=once');
        $ARRAY = $API->read();

        if ($_GET["cate"]== "download") { echo number_format($ARRAY[0]['rx-bits-per-second'] / 1024 / 1024,2);    }
        if ($_GET["cate"]== "upload") { echo number_format($ARRAY[0]['tx-bits-per-second'] / 1024 / 1024,2);    }
    }
}
$API->disconnect();

?>