/**
 * Created by KICT-20 on 2016-07-19.
 */

const electron=require('electron');
const {app}=electron;
const {BrowserWindow}=electron;
let win;

function createWindow() {
    win=new BrowserWindow({width:800,height:600});
    win.loadURL(`file://${__dirname}/index.html`);
    win.on('closed',()=>{
        win=null;
    });
}

app.on('ready',createWindow);
app.on('activate',()=>{
    if(win===null){
        createWindow();
    }
});
app.on('window-all-closed',()=>{
    if(process.platform!=='darwin'){
        app.quit();
    }
});