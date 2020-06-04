# azul

COSC1076 | Semester 1 2020 APT Assignment 2 Programming Project (Azul)

## Testing

build azul

```
make
```

run test

```
./azul -s 1 < test_fill_gameover/input
```

get difference between expected and output savegames

```
diff -q test_fill_gameover/expected/ test_fill_gameover/output/
```
