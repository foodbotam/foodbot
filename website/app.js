const md5 = require("md5");
const path = require('path');
const { log } = require("util");
const express = require('express');
const session = require("express-session");

const fs = require('fs')
const app = express();
const port = 3000;

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
	console.log(fs.existsSync(file_path));
	return fs.existsSync(file_path)
}

// Function which will make file by given name ading .json at the end
function make_json_file(name, password) {
	json_file_path = `public/devices/${md5(name)}.json`
	let jsonData = `
{
	"password" : "${md5(password)}",
	"type" : "sandwich",
	"container_1" : "bread",
	"container_2" : "tomato",
	"container_3" : "cucumber",
	"container_4" : "sosage",
	"container_5" : "ketchup",
	"container_6" : "mayonnaise",
	"container_7" : "salt",
	"container_8" : "pepper"
}
	`;
	let jsonObj = JSON.parse(jsonData);
	let jsonContent = JSON.stringify(jsonObj);
	fs.writeFile(json_file_path, jsonData, "utf8", function (err) { });
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
	res.render("login.ejs", { uorp: true })
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
				res.render("login.ejs", { uorp: false })
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
	res.render("aboutus.ejs", { uorp: req.session.loggedin })
});

// Function for home page
app.get("/home", (req, res) => {
	res.render("home.ejs", { uorp: req.session.loggedin })
});

// Function for device control page
app.get("/devicecontrol", (req, res) => {
	res.render("home.ejs", { uorp: req.session.loggedin })
});

// Function for runing logout 
app.get("/logout", (req, res) => {
	req.session.loggedin = false
	req.session.deviceid = ""
	req.session.password = ""
	res.redirect("/home")
});

// Function for showing products mady by foodbot 
app.get("/products", (req, res) => {
	res.render("products.ejs", { uorp: req.session.loggedin }	)
});

// Running server
app.listen(port, () => {
	console.log(`Example app listening on port ${port}`)
})