


# Key Classes & Responsibilities
1️⃣ Movie
Stores movie details like title, duration, language, rating, etc.

2️⃣ Theater
Each theater belongs to a city and contains multiple screens.

3️⃣ Screen
Each screen has multiple shows for different movies.

4️⃣ Show
Each show contains a movie, start time, and available seats.

5️⃣ Seat
Stores seat number, row, and booking status.

6️⃣ Booking
Handles ticket reservations and ensures seat availability before booking.



🔹 Step 1: User searches for movies in a city
Store movies and theaters in a data structure (vector/unordered_map).
Filter theaters by city and return available movies.

🔹 Step 2: User selects a theater and show
Each theater contains screens.
Each screen has multiple shows.

🔹 Step 3: User selects seats
Before confirming a booking, check if the seat is available.

🔹 Step 4: Booking a seat
If the seat is available, mark it as booked.
Store the booking details.
