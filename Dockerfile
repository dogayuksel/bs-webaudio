FROM node:10.16-alpine

RUN apk update && apk add python g++ make && rm -rf /var/cache/apk/*

RUN npm install -g bs-platform --unsafe-perm

WORKDIR /usr/app/

COPY . .

RUN yarn && yarn cache clean

RUN npm link bs-platform

RUN yarn make

RUN yarn build

RUN addgroup -S appgroup && \
    adduser -S appuser appgroup && \
    chown -R appuser:appgroup /usr/app

USER appuser

EXPOSE 3000

CMD ["yarn", "start"]
