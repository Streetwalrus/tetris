const uint8_t pieces[][4][16] =
{
    { // |
        { 0, 1, 0, 0,
          0, 1, 0, 0,
          0, 1, 0, 0,
          0, 1, 0, 0 },

        { 0, 0, 0, 0,
          1, 1, 1, 1,
          0, 0, 0, 0,
          0, 0, 0, 0 },

        { 0, 1, 0, 0,
          0, 1, 0, 0,
          0, 1, 0, 0,
          0, 1, 0, 0 },

        { 0, 0, 0, 0,
          1, 1, 1, 1,
          0, 0, 0, 0,
          0, 0, 0, 0 }
    },

    { // L
        { 0, 2, 0, 0,
          0, 2, 0, 0,
          0, 2, 2, 0,
          0, 0, 0, 0 },

        { 0, 0, 2, 0,
          2, 2, 2, 0,
          0, 0, 0, 0,
          0, 0, 0, 0 },

        { 2, 2, 0, 0,
          0, 2, 0, 0,
          0, 2, 0, 0,
          0, 0, 0, 0 },

        { 0, 0, 0, 0,
          2, 2, 2, 0,
          2, 0, 0, 0,
          0, 0, 0, 0 },
    },

    { // L mirrored
        { 0, 3, 0, 0,
          0, 3, 0, 0,
          3, 3, 0, 0,
          0, 0, 0, 0 },

        { 3, 0, 0, 0,
          3, 3, 3, 0,
          0, 0, 0, 0,
          0, 0, 0, 0 },

        { 0, 3, 3, 0,
          0, 3, 0, 0,
          0, 3, 0, 0,
          0, 0, 0, 0 },

        { 3, 3, 3, 0,
          0, 0, 3, 0,
          0, 0, 0, 0,
          0, 0, 0, 0 }
    },

    { // S
        { 0, 4, 4, 0,
          4, 4, 0, 0,
          0, 0, 0, 0,
          0, 0, 0, 0 },

        { 4, 0, 0, 0,
          4, 4, 0, 0,
          0, 4, 0, 0,
          0, 0, 0, 0 },

        { 0, 4, 4, 0,
          4, 4, 0, 0,
          0, 0, 0, 0,
          0, 0, 0, 0 },

        { 4, 0, 0, 0,
          4, 4, 0, 0,
          0, 4, 0, 0,
          0, 0, 0, 0 }
    },

    { // Z
        { 5, 5, 0, 0,
          0, 5, 5, 0,
          0, 0, 0, 0,
          0, 0, 0, 0 },

        { 0, 5, 0, 0,
          5, 5, 0, 0,
          5, 0, 0, 0,
          0, 0, 0, 0 },

        { 5, 5, 0, 0,
          0, 5, 5, 0,
          0, 0, 0, 0,
          0, 0, 0, 0 },

        { 0, 5, 0, 0,
          5, 5, 0, 0,
          5, 0, 0, 0,
          0, 0, 0, 0 }
    },

    { // Square
        { 0, 6, 6, 0,
          0, 6, 6, 0,
          0, 0, 0, 0,
          0, 0, 0, 0 },

        { 0, 6, 6, 0,
          0, 6, 6, 0,
          0, 0, 0, 0,
          0, 0, 0, 0 },

        { 0, 6, 6, 0,
          0, 6, 6, 0,
          0, 0, 0, 0,
          0, 0, 0, 0 },

        { 0, 6, 6, 0,
          0, 6, 6, 0,
          0, 0, 0, 0,
          0, 0, 0, 0 }
    },

    { // T
        { 0, 7, 0, 0,
          7, 7, 7, 0,
          0, 0, 0, 0,
          0, 0, 0, 0 },

        { 0, 7, 0, 0,
          0, 7, 7, 0,
          0, 7, 0, 0,
          0, 0, 0, 0 },

        { 0, 0, 0, 0,
          7, 7, 7, 0,
          0, 7, 0, 0,
          0, 0, 0, 0 },

        { 0, 7, 0, 0,
          7, 7, 0, 0,
          0, 7, 0, 0,
          0, 0, 0, 0 }
    }
};

