![run-tests](../../workflows/run-tests/badge.svg)

## Δομές Δεδομένων και Τεχνικές Προγραμματισμού

### Κώδικας Εργαστηρίου 4

Εκφώνηση: https://k08.chatzi.org/labs/lab4/ 

__Άσκηση 2__

* Πολυπλοκότητα naive_heapify : O(nlogn), κάνουμε n προσθήκες(inserts), όπου κάθε insert είναι Ο(logn). Άρα σύνολο : Ο(nlogn)

* Πολυπλοκότητα efficient_heapify : O(n)

__Άσκηση 3__

* Πολυπλοκότητα listify : O(nlogn) > O(n) : heapify

* Πολυπλοκότητα pqueue_create : O(nlogn) όσο η listify > O(n) : heap

* Πολυπλοκότητα pqueue_max : O(1) = heap

* Πολυπλοκότητα pqueue_remove_max : O(1) = heap

* Πολυπλοκότητα pqueue_size : O(1) = heap

* Πολυπλοκότητα pqueue_insert : O(n) > O(1) : heap

* Πολυπλοκότητα pqueue_set_destroy_value : Ο(1) = heap

* Πολυπλοκότητα pqueue_destroy : Ο(n) = heap

© Kosmas Poirazoglou, Department of Informatics and Telecommunications of the University of Athens
