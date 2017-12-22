<?php

$query = $argv[1];

$dir = iconv("UTF-8", "GBK", "/Users/qiupinduan/desktop/codes/$query");

if(is_dir($dir)==false){
	mkdir(iconv("UTF-8", "GBK", $dir),0777,true); 
}

$cpp = fopen("$dir/$query.cpp","w");
	$txt='#include <cstdlib>';
		fwrite($cpp,$txt);fwite($cpp,"\n");
	$txt='#include <cstdio>';
		fwrite($cpp,$txt);fwite($cpp,"\n");
	$txt='#include <cstring>';
		fwrite($cpp,$txt);fwite($cpp,"\n");
	$txt='#include <iostream>';
		fwrite($cpp,$txt);fwite($cpp,"\n");
	$txt='#include <algorithm>';
		fwrite($cpp,$txt);fwite($cpp,"\n");
	$txt='using namespace std;';
		fwrite($cpp,$txt);fwite($cpp,"\n");fwite($cpp,"\n");
	$txt='int main';
		fwrite($cpp,$txt);fwite($cpp,"\n");
	$txt='{';
		fwrite($cpp,$txt);fwite($cpp,"\n");
	$txt='freopen("input","r",stdin);';
		fwrite($cpp,$txt);fwite($cpp,"\n");
	$txt='return 0';
		fwrite($cpp,$txt);fwite($cpp,"\n");
	$txt='}';
		fwrite($cpp,$txt);
fclose($cpp);

$input = fopen("$dir/input","w");
	fwrite($input,'123');
fclose($input);

echo $query;

?>