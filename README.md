# Dating Stories

## Setup

### Install node

#### Using the Node.js official installer

You can find the installer on [the website](https://nodejs.org/en/)

For OSX https://nodejs.org/dist/v6.9.1/node-v6.9.1.pkg

#### Via NVM

```
$ curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.32.1/install.sh | bash
```

Open a new terminal and then you can install node with nvm

```
$ nvm install 6
$ nvm alias default 6
```

You can find more instruction [on their website](https://github.com/creationix/nvm)

### Install dependencies -- do this in the directory of the project

```
$ npm install
```

## Usage

You can run the dev server with the command

```
$ npm start
```

You can then browse to http://127.0.0.1:8080 to start working!

If you make any changes you will need to refresh the browser to see them.

You can use developer tools to get a console and debug errors in your code. For chrome the hot-key to open it is alt+command+j

Here's a video on dev tools you can watch by Jon Kuperman --> https://www.youtube.com/watch?v=ZRr9X-rD3Hc

## Common Local Development Gotcha's

q: I've made changes, but they are not showing.

a: make sure that you have "Disable cache (while DevTools is open)" turned on in the settings.

---

q: The server says that something is already using the port

a: kill all the node processes on your system with ```killall node```

