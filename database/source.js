var MongoClient = require('mongodb').MongoClient;
var url = "mongodb://localhost:27017/mydb";

MongoClient.connect(url, function(err, db) {
  if (err) throw err;
  var dbo = db.db("myemp");
  var my_employees = [
    { name: 'Amari Jocelyn Harris', title: 'Software Engineer'},
    { name: 'James', title: 'Lowstreet 4'},
    { name: 'Sumayyah', title: 'Apple st 652'}
  ];
  var amaris = { name: "Amari Harris", title: "Software Engineer" };
  dbo.collection("employees").insertMany(my_employees, function(err, res) {
    if (err) throw err;
    console.log("Number of employees added: " + res.insertedCount);
    db.close();
  });
});
