import{d as s,b as r,o as l,c as i,g as u,a as n,u as c,h as b}from"./index-e3fd19ff.js";import{a as f}from"./axios-28bc18a3.js";const p=n("br",null,null,-1),d=["disabled"],v=s({__name:"RebootView",setup(m){var o=r(!1);function a(){o.value=!0,f.get("/api/reboot").then(function(e){console.log(e),b.push({path:"/"})}).catch(function(e){console.log(e)}).finally(function(){o.value=!1})}return(e,t)=>(l(),i("main",null,[u(" Please confirm that you want to reboot board? "),p,n("button",{type:"button",class:"btn btn-primary mb-5",onClick:t[0]||(t[0]=_=>a()),disabled:c(o)},"Reboot",8,d)]))}});export{v as default};