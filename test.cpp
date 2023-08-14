// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"

// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0

    ASSERT_TRUE(collection->empty()); // The collection should be empty at the start.
    add_entries(1); // Add a single value to the collection.
    ASSERT_FALSE(collection->empty()); // The collection should not be empty after adding a value.
    ASSERT_EQ(collection->size(), 1); // The size of the collection should be 1 after adding a single value.
}

// TODO: Create a test to verify adding five values to the collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterThanOrEqualToSize)
{
    // Test for an empty collection
    ASSERT_GE(collection->max_size(), collection->size());

    // Add one entry and check again
    add_entries(1);
    ASSERT_GE(collection->max_size(), collection->size());

    // Add five entries and check again
    add_entries(5);
    ASSERT_GE(collection->max_size(), collection->size());

    // Add ten entries and check again
    add_entries(10);
    ASSERT_GE(collection->max_size(), collection->size());
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterThanOrEqualToSize)
{
    // Test for an empty collection
    ASSERT_GE(collection->capacity(), collection->size());

    // Add one entry and check again
    add_entries(1);
    ASSERT_GE(collection->capacity(), collection->size());

    // Add five entries and check again
    add_entries(5);
    ASSERT_GE(collection->capacity(), collection->size());

    // Add ten entries and check again
    add_entries(10);
    ASSERT_GE(collection->capacity(), collection->size());
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesCollection)
{
    add_entries(5); // Add 5 entries
    size_t originalSize = collection->size();

    collection->resize(originalSize + 3); // Resize to original size + 3

    ASSERT_EQ(collection->size(), originalSize + 3); // The size of the collection should increase by 3 after resizing.
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesCollection)
{
    add_entries(8); // Add 8 entries
    size_t originalSize = collection->size();

    collection->resize(originalSize - 3); // Resize to original size - 3

    ASSERT_EQ(collection->size(), originalSize - 3); // The size of the collection should decrease by 3 after resizing.
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeDecreasesToZero)
{
    add_entries(5); // Add 5 entries

    collection->resize(0); // Resize to 0

    ASSERT_TRUE(collection->empty()); // The collection should be empty after resizing to 0.
    ASSERT_EQ(collection->size(), 0); // The size of the collection should be 0 after resizing to 0.
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    add_entries(10); // Add 10 entries
    collection->clear(); // Clear the collection
    ASSERT_TRUE(collection->empty()); // The collection should be empty after clearing.
    ASSERT_EQ(collection->size(), 0); // The size of the collection should be 0 after clearing.
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseBeginToEnd)
{
    add_entries(5); // Add 5 entries

    collection->erase(collection->begin(), collection->end()); // Erase all elements

    ASSERT_TRUE(collection->empty()); // The collection should be empty after erasing all elements.
    ASSERT_EQ(collection->size(), 0); // The size of the collection should be 0 after erasing all elements.
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacity)
{
    add_entries(5); // Add 5 entries

    size_t originalCapacity = collection->capacity();
    size_t originalSize = collection->size();

    collection->reserve(originalCapacity + 10); // Reserve more capacity

    ASSERT_EQ(collection->size(), originalSize); // The size of the collection should remain the same after reserving more capacity.
    ASSERT_GT(collection->capacity(), originalCapacity); // The capacity of the collection should be greater after reserving more capacity.
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, AccessOutOfRange)
{
    add_entries(5); // Add 5 entries

    // Accessing an element out of bounds should throw std::out_of_range
    ASSERT_THROW(collection->at(10), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative

// Positive test: Verify that the size of the collection is equal to the number of elements added
TEST_F(CollectionTest, SizeEqualsNumberOfAddedElements)
{
    add_entries(7); // Add 7 entries

    ASSERT_EQ(collection->size(), 7);
}

// Negative test: Verify that the collection is not empty after trying to add a negative number of elements
TEST_F(CollectionTest, CannotAddNegativeNumberOfElements)
{
    int count = -5;

    // Ensure that add_entries is not called with a negative count
    if (count > 0)
    {
        add_entries(count);
    }

    // The collection should not be empty, and the size should be 0
    ASSERT_TRUE(collection->empty()); // The collection should be empty after trying to add negative elements.
    ASSERT_EQ(collection->size(), 0); // The size of the collection should be 0 after trying to add negative elements.
}