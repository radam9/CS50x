SELECT name FROM
(SELECT DISTINCT people.id, name FROM people
JOIN stars ON person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE year = 2004
ORDER BY birth);
