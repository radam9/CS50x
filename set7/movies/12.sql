SELECT title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE (people.name = 'Johnny Depp' OR people.name = 'Helena Bonham Carter')
GROUP BY title
HAVING count(*) = 2;
