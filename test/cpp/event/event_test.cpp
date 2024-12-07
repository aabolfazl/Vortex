#include <gtest/gtest.h>
#include "core/interfaces/event/io_uring_core.h"

namespace vortex::test {

TEST(IoUringCoreTest, BasicSystemSetup) {
    EXPECT_TRUE(event::is_io_uring_supported());
}

TEST(IoUringCoreTest, CorrectEnumValues) {
    EXPECT_EQ(static_cast<int>(event::io_request::request_type::accept), 0x1);
    EXPECT_EQ(static_cast<int>(event::io_request::request_type::connect), 0x2);
    EXPECT_EQ(static_cast<int>(event::io_request::request_type::Read), 0x4);
    EXPECT_EQ(static_cast<int>(event::io_request::request_type::Write), 0x8);
}

} // namespace vortex::test