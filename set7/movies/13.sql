SELECT name FROM
(SELECT DISTINCT name from people
JOIN stars ON person_id = people.id
WHERE movie_id IN
(SELECT movies.id FROM movies
JOIN stars ON movie_id = movies.id
JOIN people ON people.id = person_id
WHERE name = "Kevin Bacon"))
WHERE name != "Kevin Bacon";
