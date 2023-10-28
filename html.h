String htmlText = R"r(
<!DOCTYPE html>
<html lang=en>
<head>
<meta charset=UTF-8>
<meta name=viewport content="width=device-width, initial-scale=1.0">
<title>LED</title>
<style>html{height:100%;display:flex;align-items:center}body{margin-left:auto;margin-right:auto;width:100%;max-width:1000px}form{width:370px;display:flex;justify-content:center;flex-direction:column;margin:auto;margin-top:30px}form div{display:flex;justify-content:space-between}form span{margin-left:75%}</style>
</head>
<body onresize=resizeCanvas()>
<canvas id=myCanvas width=1000 height=10></canvas>
<script>function resizeCanvas(){let c=document.getElementById("myCanvas");c.width=c.parentElement.clientWidth;}
resizeCanvas();</script>
<script>let c=document.getElementById("myCanvas");let ctx=c.getContext("2d");let t=0;let len=50;let n=29;let x=0.1;let y=0;let b=10;function sin(x){return(Math.sin(Math.PI*2*x/len+(Math.PI/2)));}
function updateN(_n){n=parseInt(_n);document.getElementById("no").innerHTML=_n;}
function updateX(_n){x=parseFloat(_n);document.getElementById("xo").innerHTML=_n;}
function updateY(_n){y=parseFloat(_n);document.getElementById("yo").innerHTML=_n;}
function updateB(_n){b=parseInt(_n);document.getElementById("bo").innerHTML=_n;}
function drawStrip(brights){let grd=ctx.createLinearGradient(0,0,c.width,0);for(let i=0;i<len;i++){let b=Math.log(brights[i]+1)/5.545177444479562*255;let col=`rgb(${b},${b},${b})`;grd.addColorStop(i/len,col);}
ctx.fillStyle=grd;ctx.fillRect(0,0,c.width,c.height);}
function state(t,brightness,n,x,y){let out=new Array(len);for(let i=0;i<len;i++){out[i]=Math.round((sin(n*i+x*t)*sin(y*t)+1)/2*brightness);}
return out;}
function main(){t++;drawStrip(state(t,b,n,x,y));}
const animation=setInterval(main,40);</script>
<form action=/formhandler method=post>
<div>
<label for=n>number of bumps(0-50)</label>
<input type=range id=n name=n value=29 min=0 max=50 step=1 oninput=updateN(this.value)>
</div>
<span id=no>29</span>
<div>
<label for=x>speed along strip(0-5)</label>
<input type=range id=x name=x value=0.1 min=0 max=5 step=0.1 oninput=updateX(this.value)>
</div>
<span id=xo>0.1</span>
<div>
<label for=y>speed across strip(0-5)</label>
<input type=range id=y name=y value=0 min=0 max=5 step=0.1 oninput=updateY(this.value)>
</div>
<span id=yo>0</span>
<div>
<label for=b>brightness(0-255)</label>
<input type=range id=b name=b value=10 min=0 max=765 step=1 oninput=updateB(this.value)>
</div>
<span id=bo>10</span>
<input type=submit value=send>
</form>
<a style="display:none;" href="/wifi?pwd=***&ssid=***">change wifi network</a>
</body>
</html>)r";