# Dockerfile ENTRYPOINT vs CMD

- ENTRYPOINT

defines the executable invoked when the container is started.

- CMD

specifies the arguments that get passed to the ENTRYPOINT.

Although you can use the CMD instruction to specify the command you want to
execute when the image is run, the correct way is to do it through the
ENTRYPOINT instruction and to only specify the CMD if you want to define the
default arguments. The image can then be run without specifying any arguments.

```bash
$ docker run <image>
```

or with additional arguments, which override whatever's set under CMD in the
Dockerfile:

```bash
$ docker run <image> <arguments>
```

# Shell form vs Exec form

- shell form

```Dockerfile
ENTRYPOINT node app.js
```

- exec form

```Dockerfile
ENTRYPOINT ["node", "app.js"]
```

The difference is whether the specified command is invoked inside a shell or
not.

| Docker     | Kubernetes | Description                                         |
|------------|------------|-----------------------------------------------------|
| ENTRYPOINT | command    | The executable that's executed inside the container |
| CMD        | args       | The arguments passed to the executable              |
