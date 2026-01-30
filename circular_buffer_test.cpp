#include "circular_buffer.hpp"

#include <cstdint>
#include <stdexcept>

#include <catch2/catch_test_macros.hpp>


TEST_CASE("can_read_an_item_just_written") {
  circular_buffer::CircularBuffer buffer(1);

  int32_t value = 1;
  REQUIRE_NOTHROW(buffer.write(value));

  REQUIRE(value == buffer.read());
}


TEST_CASE("items_are_read_in_the_order_they_are_written") {
  circular_buffer::CircularBuffer buffer(2);

  REQUIRE_NOTHROW(buffer.write(1));
  REQUIRE_NOTHROW(buffer.write(2));

  int32_t expected = 1;
  REQUIRE(expected == buffer.read());

  expected = 2;
  REQUIRE(expected == buffer.read());
}

TEST_CASE("a_read_frees_up_capacity_for_another_write") {
  circular_buffer::CircularBuffer buffer(1);

  REQUIRE_NOTHROW(buffer.write(1));

  int32_t expected = 1;
  REQUIRE(expected == buffer.read());

  REQUIRE_NOTHROW(buffer.write(2));

  expected = 2;
  REQUIRE(expected == buffer.read());
}

TEST_CASE("read_position_is_maintained_even_across_multiple_writes") {
  circular_buffer::CircularBuffer buffer(3);

  REQUIRE_NOTHROW(buffer.write(1));
  REQUIRE_NOTHROW(buffer.write(2));

  int32_t expected = 1;
  REQUIRE(expected == buffer.read());

  REQUIRE_NOTHROW(buffer.write(3));

  expected = 2;
  REQUIRE(expected == buffer.read());

  expected = 3;
  REQUIRE(expected == buffer.read());
}

TEST_CASE("clear_frees_up_capacity_for_another_write") {
  circular_buffer::CircularBuffer buffer(1);

  REQUIRE_NOTHROW(buffer.write(1));

  buffer.clear();

  REQUIRE_NOTHROW(buffer.write(2));

  int32_t expected = 2;
  REQUIRE(expected == buffer.read());
}

TEST_CASE("clear_does_nothing_on_empty_buffer") {
  circular_buffer::CircularBuffer buffer(1);

  buffer.clear();

  REQUIRE_NOTHROW(buffer.write(1));

  int32_t expected = 1;
  REQUIRE(expected == buffer.read());
}

TEST_CASE("overwrite_acts_like_write_on_non_full_buffer", "[overwrite]") {
  circular_buffer::CircularBuffer buffer(2);

  REQUIRE_NOTHROW(buffer.write(1));

  buffer.overwrite(2);

  int32_t expected = 1;
  REQUIRE(expected == buffer.read());

  expected = 2;
  REQUIRE(expected == buffer.read());
}

TEST_CASE("overwrite_replaces_the_oldest_item_on_full_buffer", "[overwrite]") {
  circular_buffer::CircularBuffer buffer(2);

  REQUIRE_NOTHROW(buffer.write(1));
  REQUIRE_NOTHROW(buffer.write(2));

  buffer.overwrite(3);

  int32_t expected = 2;
  REQUIRE(expected == buffer.read());

  expected = 3;
  REQUIRE(expected == buffer.read());
}

TEST_CASE("overwrite_replaces_the_oldest_item_after_read", "[overwrite]") {
  circular_buffer::CircularBuffer buffer(3);

  REQUIRE_NOTHROW(buffer.write(1));
  REQUIRE_NOTHROW(buffer.write(2));
  REQUIRE_NOTHROW(buffer.write(3));

  int32_t expected = 1;
  REQUIRE(expected == buffer.read());

  REQUIRE_NOTHROW(buffer.write(4));

  buffer.overwrite(5);

  expected = 3;
  REQUIRE(expected == buffer.read());

  expected = 4;
  REQUIRE(expected == buffer.read());

  expected = 5;
  REQUIRE(expected == buffer.read());
}

TEST_CASE("reading_empty_buffer_should_fail", "[exception]") {
  circular_buffer::CircularBuffer buffer(1);

  REQUIRE_THROWS_AS(buffer.read(), std::domain_error);
}

TEST_CASE("each_item_may_only_be_read_once", "[exception]") {
  circular_buffer::CircularBuffer buffer(1);

  REQUIRE_NOTHROW(buffer.write(1));

  int32_t expected = 1;
  REQUIRE(expected == buffer.read());

  REQUIRE_THROWS_AS(buffer.read(), std::domain_error);
}

TEST_CASE("full_buffer_cant_be_written", "[exception]") {
  circular_buffer::CircularBuffer buffer(1);

  REQUIRE_NOTHROW(buffer.write(1));
  REQUIRE_THROWS_AS(buffer.write(2), std::domain_error);
}

TEST_CASE("items_cleared_out_of_buffer_cant_be_read", "[exception]") {
  circular_buffer::CircularBuffer buffer(1);

  REQUIRE_NOTHROW(buffer.write(1));

  buffer.clear();

  REQUIRE_THROWS_AS(buffer.read(), std::domain_error);
}

TEST_CASE("full_buffer_cant_be_written_after_overwrite",
          "[overwrite][exception]") {
  circular_buffer::CircularBuffer buffer(1);

  REQUIRE_NOTHROW(buffer.write(1));
  buffer.overwrite(2);
  REQUIRE_THROWS_AS(buffer.write(3), std::domain_error);

  int32_t expected = 2;
  REQUIRE(expected == buffer.read());
}

TEST_CASE("initial_clear_does_not_affect_wrapping_around",
          "[overwrite][exception]") {
  circular_buffer::CircularBuffer buffer(2);

  buffer.clear();

  REQUIRE_NOTHROW(buffer.write(1));
  REQUIRE_NOTHROW(buffer.write(2));

  buffer.overwrite(3);
  buffer.overwrite(4);

  int32_t expected = 3;
  REQUIRE(expected == buffer.read());

  expected = 4;
  REQUIRE(expected == buffer.read());

  REQUIRE_THROWS_AS(buffer.read(), std::domain_error);
}
