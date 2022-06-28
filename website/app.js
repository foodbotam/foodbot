const md5 = require("md5");
const path = require('path');
const { log } = require("util");
const express = require('express');
const session = require("express-session");

const fs = require('fs');
const { connect } = require("http2");
const app = express();
const port = 3000;
const au = "d6ca3fd0c3a3b462ff2b83436dda495e"
const ap = "553225726ea919e57e3d61bcaf4a1b24"


var admin_loggedin = false;
var language = "am";
var translated = JSON.parse(fs.readFileSync("translation.json"));

// Defining server proparties
app.set("view engine", "ejs");
app.use(express.urlencoded());
app.use(express.static('public'))
app.use(session({
	secret: "dbec174f7b9410798058da89188f2f4c",
	resave: false,
	saveUninitialized: true
}));
app.use(express.static(__dirname + '/public'));


// Function which will return true if file exist or false if not exist
function check_file_exist(name) {
	const file_path = path.join(__dirname, `public/devices/${md5(name)}.json`)
	return fs.existsSync(file_path)
}

// Function which will make file by given name ading .json at the end
function make_json_file(name, password) {
	json_file_path = `public/devices/${md5(name)}.json`
	let jsonData = `
{
	"password" : "${md5(password)}",
	"type" : "sandwich",
	"container_1" : {"name" : "bread" , "image_path" : "images/sandwich/bread.png"},
	"container_2" : {"name" : "tomato", "image_path" : "images/sandwich/tomato.png"},
	"container_3" : {"name" : "cucumber", "image_path" : "images/sandwich/cucumber.png"},
	"container_4" : {"name" : "sausage", "image_path" : "images/sandwich/sausage.png"},
	"container_5" : {"name" : "ketchup", "image_path" : "images/sandwich/ketchup.png"},
	"container_6" : {"name" : "mayonnaise", "image_path" : "images/sandwich/mayonnaise.png"},
	"container_7" : "salt",
	"container_8" : "pepper"
}
	`;
	let jsonObj = JSON.parse(jsonData);
	let jsonContent = JSON.stringify(jsonObj);
	fs.writeFileSync(json_file_path, jsonData, "utf8", function (err) { });
}

function edit_container(container, newname, device_id){
	let json_file_path = `public/devices/${md5(device_id)}.json`
	let json_data =  JSON.parse(fs.readFileSync(json_file_path));
	if (newname=="cucumber" || newname=="sausage" || newname=="tomato" || newname=="cheese" || newname=="onion" || newname=="green_pepper" || newname=="ketchup" || newname=="mayonnaise" || newname=="mustard") {
		json_data[container]["name"] = newname
		json_data[container]["type"] = "special"
		json_data[container]["image_path"] = `images/sandwich/${newname}.png`
		let jsonContent = JSON.stringify(json_data);
		fs.writeFile(json_file_path, jsonContent, "utf8", function (err) { });
	}
	else {
		json_data[container]["name"] = newname
		json_data[container]["type"] = "other"
		if(container=="container_1" || container=="container_2" || container=="container_3" || container=="container_4"){
			json_data[container]["image_path"] = `images/sandwich/anotherfood.png`
		}
		if(container=="container_5" || container=="container_6"){
			json_data[container]["image_path"] = `images/sandwich/anothersauce.png`
		}
		let jsonContent = JSON.stringify(json_data);
		fs.writeFile(json_file_path, jsonContent, "utf8", function (err) { });
	}
}

// Function for reading json file 
function read_device_info(name){
	let json_file_path = `public/devices/${md5(name)}.json`
	let json_data =  JSON.parse(fs.readFileSync(json_file_path));
	return json_data
}

// Function which will check if password is true	
function check_password(name, password) {
	let json_file_path = `public/devices/${md5(name)}.json`
	let json_data =  JSON.parse(fs.readFileSync(json_file_path));
	let real_password = json_data["password"]
	return real_password == md5(password)
}


// Website URL redirects to /home
app.get("/", (req, res) => {
	res.redirect("/home")
}
);

// Function for rendering login page
app.get("/login", (req, res) => {
	res.render("login.ejs", { uorp: true, translated: translated, language: language })
});

// Function which will work when user login
app.post("/login", (req, res) => {
	let deviceid = req.body.deviceid
	let password = req.body.password
	if (req.session.loggedin) {
		res.redirect("/devicecontrol")
	}
	else {
		if (check_file_exist(deviceid)) {
			if (check_password(deviceid, password)) {
				req.session.loggedin = true;
				req.session.deviceid = deviceid;
				req.session.password = password;
				res.redirect("/devicecontrol")
			}
			else
			{
				res.render("login.ejs", { uorp: false , translated: translated, language: language})
			}
		}
		else {
			make_json_file(deviceid, password)
			res.redirect("/devicecontrol")
		}
	}
});

// Function for aboutus page
app.get("/aboutus", (req, res) => {
	res.render("aboutus.ejs", { uorp: req.session.loggedin, language: language, translated: translated })
});

// Function for home page
app.get("/home", (req, res) => {
	res.render("home.ejs", { uorp: req.session.loggedin, language: language, translated: translated })
});

// Function for device control page
app.get("/devicecontrol", (req, res) => {
	if (req.session.loggedin){
		res.render("devicecontrol.ejs", { uorp: req.session.loggedin, data: read_device_info(req.session.deviceid), language: language, translated: translated})
	}
	else{
		res.redirect("/login")
	}
});

// Function for device control page
app.get("/editcontainers", (req, res) => {
	if (req.session.loggedin){
		res.render("editcontainers.ejs", { uorp: req.session.loggedin, data: read_device_info(req.session.deviceid), language: language, translated: translated})
	}
	else{
		res.redirect("/login")
	}
});

// Function for runing logout 
app.get("/logout", (req, res) => {
	req.session.loggedin = false
	req.session.deviceid = ""
	req.session.password = ""
	res.redirect("/home")
});

// Function for runing admin logout 
app.get("/adminlogout", (req, res) => {
	req.session.admin_loggedin = false
	admin_loggedin = false
	res.redirect("/home")
});

// Function for showing products mady by foodbot 
app.get("/products", (req, res) => {
	res.render("products.ejs", { uorp: req.session.loggedin, language: language, translated: translated })
});

// If you post on this url you will change language
app.get("/changelanguage", (req, res) => {
	res.redirect("/home")
}
);

app.post("/changelanguage/:selected_language", (req, res) => {
	language = req.params.selected_language
	if (language=="armenian")
	{
		language = "am"
	}
	else if (language=="english")
	{
		language = "en"
	}
	else if (language=="russian")
	{
		language = "ru"
	}
});



app.post("/changecontainer/:container/:newitem", (req, res) => {
	let container = req.params.container
	let newname = req.params.newitem
	edit_container(container, newname, req.session.deviceid)
});



// Function for opening admin page
app.get("/admin", (req, res) => {
	if (admin_loggedin){
		res.render("admin.ejs", {uorp: admin_loggedin, translated: translated, language: language, error: "noerror"})
	}
	else{
		res.render("adminlogin.ejs", {uorp: admin_loggedin, translated: translated, language: language, error: "noerror"})
	}
}
);

// Function for opening admin page
app.post("/admin", (req, res) => {
	if (req.body.newdevicename) {
		make_json_file(req.body.newdevicename, req.body.newdevicepassword)
		if (admin_loggedin){
			res.render("admin.ejs", {uorp: admin_loggedin, translated: translated, language: language, error: "success_device_add"})
		}
		else{
			res.render("adminlogin.ejs", {uorp: admin_loggedin, translated: translated, language: language, error: "noerror"})
		}
	}
	else{
		if (md5(req.body.adminusername)==au && md5(req.body.adminpassword)==ap){
			admin_loggedin = true;
			res.redirect("/admin")
		}
		else{
			res.render("adminlogin.ejs",{uorp : false, translated: translated, language: language, error: "admin_login_error"})
		}
	}
});

// Running server
app.listen(port, () => {
	console.log(`Program started runing. Open  http://localhost:${port}`)
})