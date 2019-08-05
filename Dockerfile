# Use an official Node runtime as a parent image
FROM node:10

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app

# Install app dependencies
# A wildcard is used to ensure both package.json AND package-lock.json are copied
# where available (npm@5+)
COPY package*.json ./

RUN npm install
# If you are building your code for production
# RUN npm ci --only=production

COPY . .

# Make port 80 available to the world outside this container
EXPOSE 80

# Define environment variable
ENV NAME World

# Run app.py when the container launches
CMD ["node", "server.js"]
