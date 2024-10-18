#### Programming Task: RAII Booking

In the lecture, we wrote a `TripManager` class for booking a set of flights and hotels, using the auxiliary classes `FlightProvider` and `HotelProvider`. Following the RAII idiom, we moved the booked set into a separate `Trip` class. The code written during the lecture was slightly modified and placed in the files `old_booking_providers.h` and `old_trip_manager.h`.

You are now tasked with making individual flight and hotel bookings follow the RAII pattern as well. This will simplify the `Trip` class: in its `Cancel` function, there will be no need to explicitly call booking cancellations—simply deleting elements from the vectors will be enough.

You are provided with new versions of the `TripManager`, `Trip`, `FlightProvider`, and `HotelProvider` classes, which are located in the files `new_booking_providers.h` and `new_trip_manager.h`. In the new classes, the `Cancel` function has been renamed to `CancelOrComplete`: it should automatically be called not only when the booking is canceled but also when it is successfully completed. Now, the `Book` and `CancelOrComplete` functions in the provider classes return and accept not a `BookingId`, but a special class that you need to create.

Since `FlightProvider` and `HotelProvider` have the same interface, in order to avoid code duplication, we ask you to design a template class `Booking<Provider>`, where the template type will be either `FlightProvider` or `HotelProvider`.

Submit a file named `booking.h` to the testing system, which:

- Contains the `RAII` namespace.
- Inside the `RAII` namespace, contains the definition of the template class `Booking<Provider>`.

The interface of the `Booking<Provider>` class should become clear to you after studying the files `new_booking_providers.h` and `new_trip_manager.h`.

For testing convenience, we have made the booking counter and the maximum allowed number of bookings public static variables of the `FlightProvider` and `HotelProvider` classes.

---

This translation retains the technical details and context of the task. Let me know if you need further assistance with implementing the solution!