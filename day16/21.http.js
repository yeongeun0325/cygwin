/**
 * Created by KICT-20 on 2016-07-19.
 */

const http=require('http');
const util=require('util');
const os=require('os');
const UrlParser=require('url');

let solution;
let solved=false;
let AdminPsw="ye"
let winnername="";

let http_server=http.createServer((req,res)=>{
    console.log(req.url);

    var url_obj=UrlParser.parse(req.url,true);
    console.log(url_obj)

    let header={
        'Access-Control-Allow-Origin':'*',
        'Access-Control-Allow-Method':'GET',
        "Access-Control-Max-Age":'1000'
    };
    header['Content-Type']='text/plain';
    res.writeHead(200,header);
    switch(url_obj.pathname) {
        case '/sum':
            let c = parseInt(url_obj.query.a) + parseInt(url_obj.query.b);
            res.end("result=" + c);
            break;
        case '/game-try':
            if (solved == false) {
                if (url_obj.query.value == solution) {
                    winnername=url_obj.query.name;
                    solved=true;
                    res.end('bingo!');
                }
                else if(url_obj.query.value>solution){
                    res.end("high");
                }
                else if(url_obj.query.value<solution) {
                    res.end("low");
                }
            }
            else {
                res.end(solution+"is solution game over,winner is"+winnername);
            }
            break;
        case '/start-game':
            if(url_obj.query.passwd==AdminPsw){
                solution = Math.round(Math.random() * 100);
                solved=false;
                winnername="";
                res.end("start ok:"+solution)
            }
            else{
                res.end('wrong password');
            }
        default:
            res.end("it is bingo api server");
            break;
    }

});
http_server.listen(8080);