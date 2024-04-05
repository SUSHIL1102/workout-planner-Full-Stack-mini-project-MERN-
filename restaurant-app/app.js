const express = require('express');
const bodyParser = require('body-parser');
const { MongoClient, ObjectId } = require('mongodb');

const app = express();
const PORT = 3000;
const MONGO_URL = 'mongodb+srv://sushilbhoomraddi:sushil123@restaurants.2zfjjo6.mongodb.net/?retryWrites=true&w=majority';
const DB_NAME = 'Bangalore_City';

app.use(bodyParser.json());

// MongoDB connection
// MongoDB connection
let db;

MongoClient.connect(MONGO_URL, (err, client) => {
  if (err) throw err;
  console.log('Connected to MongoDB');
  db = client.db(DB_NAME);
});


// Create a new restaurant
app.post('/restaurants', (req, res) => {
  const newRestaurant = req.body;

  db.collection('restaurants').insertOne(newRestaurant, (err, result) => {
    if (err) {
      res.status(500).send('Error adding restaurant');
    } else {
      res.status(201).send('Restaurant added successfully');
    }
  });
});

// Read all restaurants
app.get('/restaurants', (req, res) => {
  db.collection('restaurants').find({}).toArray((err, restaurants) => {
    if (err) {
      res.status(500).send('Error fetching restaurants');
    } else {
      res.json(restaurants);
    }
  });
});

// Update a restaurant's grade
app.put('/restaurants/:id', (req, res) => {
  const restaurantId = req.params.id;
  const newGrade = req.body.rest_reviews;

  db.collection('restaurants').updateOne(
    { _id: ObjectId(restaurantId) },
    { $set: { rest_reviews: newGrade } },
    (err, result) => {
      if (err) {
        res.status(500).send('Error updating restaurant grade');
      } else {
        res.status(200).send('Restaurant grade updated successfully');
      }
    }
  );
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
