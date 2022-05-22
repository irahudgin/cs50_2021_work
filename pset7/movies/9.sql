SELECT DISTINCT name FROM people
JOIN stars ON people.id=stars.person_id
WHERE stars.movie_id IN
(SELECT movie_id FROM stars 
JOIN movies ON stars.movie_id=movies.id
WHERE movies.year=2004) ORDER BY people.birth;