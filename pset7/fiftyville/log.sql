-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Description of CRIME
SELECT description FROM crime_scene_reports
WHERE year=2020 AND month=7 AND day=28 AND street="Chamberlin Street";
-- 10:15am Chamberlin Street courthouse, 3 witnesses ^
SELECT license_plate, minute FROM courthouse_security_logs
WHERE year=2020 AND month=7 AND day=28 AND hour=10 AND activity="exit" AND minute BETWEEN 15 AND 25;
-- license plates of potential thieves
SELECT COUNT(transcript) FROM interviews 
WHERE year=2020 AND month=7 AND day=28;
-- Saw thief withdrawing money from Fifer Street ATM jul 28 2020 in morning
-- Within ten minutes of theft
-- Less than a minute phone call jul 28 2020, leaving courthouse
-- Earliest flight out of fiftyville jul 29 2020, someone else bought the ticket
SELECT phone_number FROM people
WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs 
WHERE year=2020 AND month=7 AND day=28 AND hour=10 AND activity="exit" AND minute BETWEEN 15 AND 25)
INTERSECT
SELECT caller FROM phone_calls 
WHERE year=2020 AND month=7 AND day=28 AND duration<60;

-- Phone numbers of people whos license plates were within the time frame, and whos duration was below a minute
-- SELECT id FROM flights
-- WHERE year=2020 AND day=29 AND month=7 AND hour<9 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville") ORDER BY hour
-- id 36 is flight which suspect wanted to take
SELECT passport_number FROM passengers
WHERE flight_id=(SELECT id FROM flights
WHERE year=2020 AND day=29 AND month=7 AND hour<9 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville"));
-- Passports of potential suspects

SELECT name FROM people
WHERE id=(

SELECT id FROM people

WHERE phone_number IN (

SELECT phone_number FROM people 
JOIN passengers ON people.passport_number=passengers.passport_number
WHERE people.passport_number IN (SELECT passport_number FROM passengers
WHERE flight_id=(SELECT id FROM flights
WHERE year=2020 AND day=29 AND month=7 AND hour<9 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville")))
INTERSECT
SELECT phone_number FROM people
WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs 
WHERE year=2020 AND month=7 AND day=28 AND hour=10 AND activity="exit" AND minute BETWEEN 15 AND 25)
INTERSECT
SELECT caller FROM phone_calls 
WHERE year=2020 AND month=7 AND day=28 AND duration<60)
INTERSECT
--Phone number of 3 possible people, need to find out the phone number of who was at the bank that morning
SELECT person_id FROM bank_accounts
WHERE account_number IN (

SELECT account_number FROM atm_transactions
WHERE year=2020 AND month=7 AND day=28 AND atm_location="Fifer Street" AND transaction_type="withdraw"));
-- thief is ernest

SELECT name FROM people 
WHERE phone_number=(
SELECT receiver FROM phone_calls
WHERE year=2020 AND month=7 AND day=28 AND duration<60 AND caller=(
SELECT phone_number FROM people
WHERE name="Ernest"));
-- accomplice

SELECT city FROM airports
WHERE id=(
SELECT destination_airport_id FROM flights
WHERE id=(SELECT id FROM flights
WHERE year=2020 AND day=29 AND month=7 AND hour<9 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville")));

