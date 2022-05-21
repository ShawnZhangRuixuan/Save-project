const fs = require("fs");
const http = require("http");
const https = require("https");
const appid = "35a325b2216fff651e0a2455d65e8696";
const port = 3000;
let count = {task_count:0};

const server = http.createServer();
server.on("listening", listen_handler);
server.listen(port);
function listen_handler(){
	console.log(`Now Listening on Port ${port}`);
}

server.on("request", request_handler);
function request_handler(req,res){
    console.log(`New Request from ${req.socket.remoteAddress} for ${req.url}`);
    if(req.url==="/"){
        const form = fs.createReadStream("html/index.html");
        res.writeHead(200,{"Content-Type":"text/html"})
        form.pipe(res);
    }
    else if (req.url.startsWith("/enter_city")){
        const user_input = new URL(req.url, `https://${req.headers.host}`).searchParams;
        const location = user_input.get(`location`)
        console.log(location);
        if(location == null || location ==""){
            res.writeHead(404,{"Content-Type": "text/html"});
            res.end("<h1>No input</h1>");
        }
        else{
            get_all_information(location,res);
        }
    }
    else{
        res.writeHead(404,{"Content-Type": "text/html"});
        res.end('<h1>404 Not Found</h1>');
    }
}

function get_all_information(location,res){
    console.log(count.task_count);
    if(count.task_count===0 || count.task_count%2 ===0){
        const weather_api = https.request(`https://api.openweathermap.org/data/2.5/weather?q=${location}&appid=${appid}`,{method:"GET"});
        weather_api.once("response", stream => process_stream(stream,parse_weather,count,location,res));
        weather_api.end();
    }
    else if(count.task_count%2 === 1){
        const dogfacts_api = https.request(`https://dog-api.kinduff.com/api/facts`,{method:"GET"});
        dogfacts_api.once("response", stream => process_stream(stream,parse_dogfacts,count,location,res));
        dogfacts_api.end();
    }
}
function process_stream(stream,callback, ...args){
    let body ="";
    stream.on("data",chunk => body += chunk);
    stream.on("end", ()=>callback(body,...args));   
}

function parse_weather(weather_data,count,location,res){
    let weather_object = JSON.parse(weather_data);
    let mainresultOfWeather = weather_object.weather[0].main;
    let descriptionofweather = weather_object.weather[0].description;
    let feelslikeofweather = weather_object.main.feels_like - 273;
    let countryofweather = weather_object.sys.country;
    console.log(mainresultOfWeather,descriptionofweather,feelslikeofweather,countryofweather);
    res.write(`<p> Today's weahter is ${mainresultOfWeather}</p><ul><li> Today is ${descriptionofweather}.</li><li> Today feels like ${Math.round(feelslikeofweather)} degree.</li><li> This is from ${countryofweather}.</li>`,()=>stop(count,location,res));
    console.log(count);
}
function parse_dogfacts(dogfacts_data,count,location,res){
    let dogfacts_object = JSON.parse(dogfacts_data)
    let resultOfDog = dogfacts_object.facts[0];
    console.log(resultOfDog);
    res.write(`<p style="width:49%; float:left;"> Do you know that? ${resultOfDog}</p>`,()=>stop(count,location,res));
}
function stop(count,location,res){
    count.task_count++;
    console.log(count.task_count);
    if(count.task_count%2 ===0){
        console.log(`good`);
        res.end();
        count={task_count:0};
        console.log(count.task_count);
    }
    else{
        get_all_information(location,res);
    }
}
