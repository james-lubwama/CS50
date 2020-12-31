SELECT DISTINCT name
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people on person_id = people.id
WHERE movies.year = "2004"
ORDER BY people.birth;