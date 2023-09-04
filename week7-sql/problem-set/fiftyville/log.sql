-- Keep a log of any SQL queries you execute as you solve the mystery.

-- search crime_scene_reports table for the date and place of the theft

SELECT * FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28
AND street LIKE '%humphrey street%';

-- theft took place at 10:15 am at humphrey street bakery
-- there were interviews with three witnesses that same day
-- all of them mentioned the bakery

-- search for interviews in the interviews table

SELECT * FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28
AND transcript LIKE '%bakery%';

-- witnesses are named Ruth, Eugene y Raymond
-- cars in the parking lot of the bakery within 10 minutes of the theft
-- atm on leggett street earlier that morning, recognized by eugene
-- phone call after the robbery, first flight out of fiftyville the day after

-- check bakery security logs within 10 minutes of 10:15 am the day of the robbery

SELECT license_plate FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute >= 15
AND minute <= 25;

-- check people with those license plates

SELECT * FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25
);

-- check first flight out of fiftyville on july 29, 2021
SELECT id FROM flights
WHERE origin_airport_id = (
    SELECT id FROM airports
    WHERE city LIKE '%fiftyville%'
) 
AND year = 2021 
AND month = 7 
AND day = 29 
ORDER BY year, month, day, hour, minute
LIMIT 1;

-- check passengers in that flight

SELECT passport_number FROM passengers
WHERE flight_id = (
    SELECT id FROM flights
    WHERE origin_airport_id = (
        SELECT id FROM airports
        WHERE city LIKE '%fiftyville%'
    ) 
    AND year = 2021 
    AND month = 7 
    AND day = 29 
    ORDER BY year, month, day, hour, minute
    LIMIT 1
);

-- list people that were in that flight

SELECT * FROM people
WHERE passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id = (
        SELECT id FROM flights
        WHERE origin_airport_id = (
            SELECT id FROM airports
            WHERE city LIKE '%fiftyville%'
        ) 
        AND year = 2021 
        AND month = 7 
        AND day = 29 
        ORDER BY year, month, day, hour, minute
        LIMIT 1
    )
);

-- check people who were in the parking lot of the bakery and took that flight

SELECT * FROM people
WHERE passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id = (
        SELECT id FROM flights
        WHERE origin_airport_id = (
            SELECT id FROM airports
            WHERE city LIKE '%fiftyville%'
        ) 
        AND year = 2021 
        AND month = 7 
        AND day = 29 
        ORDER BY year, month, day, hour, minute
        LIMIT 1
    )
) AND license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25
);

-- check if some of the phones of the made a phone call that day

SELECT * FROM people
WHERE passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id = (
        SELECT id FROM flights
        WHERE origin_airport_id = (
            SELECT id FROM airports
            WHERE city LIKE '%fiftyville%'
        ) 
        AND year = 2021 
        AND month = 7 
        AND day = 29 
        ORDER BY year, month, day, hour, minute
        LIMIT 1
    )
) AND license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25
) AND phone_number IN (
    SELECT caller FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
);

-- Sofia id is 398010
-- Kelsey id is 560886
-- Bruce id is 686048

-- check if any of the suspects used the atm at leggett street that day

SELECT * FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE account_number IN (
            SELECT account_number FROM bank_accounts
            WHERE person_id = 398010 OR person_id = 560886 OR person_id = 686048
        ) AND year = 2021 AND month = 7 AND day = 28
    )
);

-- Bruce is the thief

-- check the destination of the flight

SELECT * FROM airports
WHERE id = (
    SELECT destination_airport_id FROM flights
    WHERE origin_airport_id = (
        SELECT id FROM airports
        WHERE city LIKE '%fiftyville%'
    ) 
    AND year = 2021 
    AND month = 7 
    AND day = 29 
    ORDER BY year, month, day, hour, minute
    LIMIT 1
);

-- Bruce went to New York City

-- check the people that bruce phoned

SELECT * FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls
    WHERE caller = (
        SELECT phone_number FROM people
        WHERE id = 686048
    ) AND year = 2021 AND month = 7 AND day = 28
);

-- Possible suspects are Gregory, Carl, Robin and Deborah
-- Robin doesnt have a passport number in the database
-- check if the other suspects were in the flight with id = 36

SELECT * FROM passengers
WHERE flight_id = 36 
AND passport_number IN (
    SELECT passport_number FROM people
    WHERE phone_number IN (
        SELECT receiver FROM phone_calls
        WHERE caller = (
            SELECT phone_number FROM people
            WHERE id = 686048
        ) AND year = 2021 AND month = 7 AND day = 28
    )
);

-- none of the other suspects were in that flight, so Robin must be the accomplice