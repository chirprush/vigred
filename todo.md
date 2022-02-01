- [X] Integrate key events into buffers
- [X] Add the hyper mod
- [X] Probably rename vi_byte_buffer (vi_scratch_buffer, vi_anon_buffer, vi_anonymous_buffer (as in how mmap calls allocations not backed by a file))?
- [X] Implement a vi_view struct and let buffers render to SDL_Surface's and blit into the bounds of the view
- [X] Add font styling
- [X] Handle mouse click events
- [ ] Handle mouse scroll events
- [ ] Implement resizing for vi_view (we need to create a new SDL_Surface for it)
- [ ] Add a vi_widget polymorphic struct for the actual UI (this will help for splits and such)
- [ ] Create a basic interface for config plugins
  - Look into shared libraries and dlfcn
- [ ] Make some basic tests for the non-rendering parts
- [ ] Get a working implementation of the B-tree file representation to render and *benchmark*