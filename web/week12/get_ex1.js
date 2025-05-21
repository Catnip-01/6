var express = require('express');
var app = express();
app.use(express.static('public'));

app.get("/index.html", function(req, res) {
    res.sendFile(__dirname + "/index.html");
});

app.get("/process_get", function(req, res){
    response = {
        firstName:req.query.fname,
        lastName:req.query.lname

    }

    console.log(response);

})

var server = app.listen(5000, function(){
    var host = server.address().address;
    var port = server.address().port;

    console.log("Example app listening at http://%s:%s", host, port);
});