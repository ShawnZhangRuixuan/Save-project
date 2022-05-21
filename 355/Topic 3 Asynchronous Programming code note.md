//How to use callback
const fs=require("fs"); //in this code, we need to read file
fs.readFile("input/file01.txt","utf8"),do_after_reading); //fs.readFile can read input file and decode by utf8, and after read file, we use callback to do next.
function do_after_reading(err,data){  //define function and there are regular parameters.
    if(err){
        console.log('Error reading File'); //if error, will print error.
    }
    else{
        console.log('Finished Reading file: ', data.length); //will print out length of data(11).
    }
}

//DNS resolution
const dns=require("dns"); //requirement statement like import
const venus="venus.cs.qc.cuny.edu"; 
const mars= "mar.cs.qc.cuny.edu";

dns.resolve(venus.after_venus); //function will not block.
console.log("prints immediately 01"); 
//always print first because dns.resolve is asynchronous call and it goes in to task queue.event loop will only put function into v8 stack when console.log is finished. Therefore, console.log is blocking. This is why this always print first.

function after_venus (err, records){
    if(err){
        console.error("Failed to resolve", venus);
    }
    esle{
        console.log(venus, records);
    }
}
dns.resolve(mars,after_mars);
cosole.log("prints Immediately 02");// always print first
function after_mars(err, records){
    if(err){
        console.error("Failed to resolve", mars);
    }
    esle{
        console.log(mars, records);
    }
}

//This is a incorrect example becuase next_task is not in function after_resolution.
const dns = require("dns");
const domain = "venus.cs.qc.cuny.edu";
let data;
 
dns.resolve(domain, after_resolution);
function after_resolution(err, records){
    if(err){
        console.error("Failed to resolve", domain);
    }
    else{
        data = records;
    }
}
next_task(data); //data will be undefined. Same as pervious one, callback step will be moved into event queue. Event loop will keeping checking v8 is it empty or not. This step will be done first than callback. correct opition is move this line into callback function.
function next_task(input){ //make anohter function for next task.
    console.log(input);}
    
//save two domains
const dns = require("dns");
const venus = "venus.cs.qc.cuny.edu";
const mars  = "mars.cs.qc.cuny.edu";
const ip_addresses = []; //make a empty arrary that we can put two ip addresses.
 
dns.resolve(venus, after_venus);
function after_venus(err, records){
    if(err){
        console.error("Failed to resolve", venus);
    }
    else{
        ip_addresses.push(records); //push venus's record into ip_address
    }
    dns.resolve(mars, after_mars); //this is in callback function so it always do after venus.
}
function after_mars(err, records){
    if(err){
        console.error("Failed to resolve", mars);
    }
    else{
        ip_addresses.push(records);
    }
    console.log(ip_addresses.join(", "));
}

//Concurrency (order will not always same it depends on which domains will be solved fisrt)
const dns = require("dns");
const venus = "venus.cs.qc.cuny.edu";
const mars  = "mars.cs.qc.cuny.edu";
 
dns.resolve(venus, after_venus);
console.log("Prints Immediately 01"); //always print first
function after_venus (err, records){
    if(err){
        console.error("Failed to resolve", venus);
    }
    else{
        console.log(venus, records);
    }
}
 
dns.resolve(mars, after_mars);
console.log("Prints Immediately 02"); //always print first
function after_mars(err, records){
    if(err){
        console.error("Failed to resolve", mars);
    }
    else{
        console.log(mars, records);
    }
}

//compressing with deflate
//reencoding and get fewer byte.

const fs = require("fs");
const zlib = require("zlib");
const output_file = "./output/content.deflated";
const content = `Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Montes nascetur ridiculus mus mauris. Ut tortor pretium viverra suspendisse potenti nullam ac tortor. Cras fermentum odio eu feugiat pretium nibh ipsum. Dictum fusce ut placerat orci nulla pellentesque dignissim enim sit. Felis eget nunc lobortis mattis aliquam. Ac placerat vestibulum lectus mauris ultrices eros in cursus. Interdum varius sit amet mattis vulputate. Nibh cras pulvinar mattis nunc sed blandit. Tristique nulla aliquet enim tortor at auctor urna nunc id. Sed euismod nisi porta lorem mollis aliquam ut porttitor. Leo integer malesuada nunc vel. Nulla aliquet enim tortor at auctor. Blandit massa enim nec dui nunc mattis enim. Egestas tellus rutrum tellus pellentesque eu. Nec dui nunc mattis enim ut tellus elementum sagittis. Adipiscing bibendum est ultricies integer quis. Tortor at risus viverra adipiscing at in tellus integer feugiat. Arcu vitae elementum curabitur vitae nunc sed velit. Ac tortor dignissim convallis aenean et tortor at. Suscipit tellus mauris a diam maecenas. Nulla aliquet enim tortor at auctor urna nunc id. Venenatis cras sed felis eget velit aliquet sagittis id.`;

zlib.deflate(content, after_compress); //(message, callback)
function after_compress(err, buffer){ //regular parameters err and buffer
    if(err){
        console.log(err);
    }
    else{
        fs.writeFile(output_file, buffer, function after_write(err){ // (path,buffer,callback). Have to write into after_compress because we need to wrrite in file ater it compressed. function after_write is also need to be in after_compress because buffer is scoped in after_compress.
            if(err){
                console.log(err);
            }
            else{
                console.log(`File Written to "${output_file}"`);
                console.log(`Original Size: ${content.length}`); //print original size
                console.log(`New Size: ${buffer.length}`);//will print size after compressed
            }
        });
    }
}

/* 01 - Deompressing with Inflate */
const fs = require("fs");
const zlib = require("zlib");
const input_file = "./input/content.deflated";

fs.readFile(input_file, {encoding:null}, function after_read(err, data){ //have to read input file to inflat.parameter: (path,encoding type, callback)
    if(err){
        console.log(err);
    }
    zlib.inflate(data, function after_decompress(err, buf){ //(date after read, decompress call back(err, buffer)
        if(err){
            console.log(err);
        }
        else{
            console.log(buf.toString("utf8"));//encoding format,usually use utf8
            console.log(`======================================`);
            console.log(`Compressed Size : ${data.length}`);
            console.log(`Decompressed Size : ${buf.length}`);
            console.log(`======================================`);
        }
    });
});

