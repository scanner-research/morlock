/* Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "hwang/mp4_index_creator.h"
#include "hwang/util/fs.h"
#include "hwang/tests/videos.h"

#include <gtest/gtest.h>

#include <thread>

namespace hwang {

TEST(MP4IndexCreator, SimpleTest) {
  // Download video file
  std::vector<uint8_t> video_bytes =
      //read_entire_file(download_video(test_video));
  read_entire_file("/h/apoms/repos/scanner/2001_A_Space_Odyssey.mp4");

  MP4IndexCreator indexer(video_bytes.size());

  uint64_t current_offset = 0;
  uint64_t size_to_read = std::min((size_t)1024, video_bytes.size());
  while (!indexer.is_done()) {
    indexer.feed(video_bytes.data() + current_offset, size_to_read,
                 current_offset, size_to_read);
    printf("offset to read %lu, size %lu\n", current_offset,
           size_to_read);
  }
  assert(!indexer.is_error());
  indexer.get_video_index();
}

}
