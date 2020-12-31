SELECT DISTINCT name
FROM (SELECT movies.id AS movieid FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id
WHERE people.name = "Kevin Bacon"
AND people.birth = 1958)

JOIN stars ON movieid = stars.movie_id
JOIN people ON people.id = stars.person_id
WHERE NOT name = "Kevin Bacon"