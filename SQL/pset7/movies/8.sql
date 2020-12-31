SELECT name
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people on person_id = people.id
WHERE title = "Toy Story";