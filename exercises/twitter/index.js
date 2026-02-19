// State
const state = {
  tweets: [
    {
      id: 1,
      name: "Richard Feldman",
      handle: "@rtfeldman",
      time: "2h",
      text: "Writing a web server in C is one of the best ways to understand what HTTP actually is.",
      likes: 841,
      retweets: 203,
      replies: 47,
      liked: false,
      retweeted: false,
    },
    {
      id: 2,
      name: "Noel Felix",
      handle: "@noelfelix",
      time: "4h",
      text: "Just learned about sendfile(2) — the kernel handles copying file bytes to a socket without touching userspace. Zero-copy FTW 🚀",
      likes: 312,
      retweets: 88,
      replies: 19,
      liked: false,
      retweeted: false,
    },
    {
      id: 3,
      name: "Low Level TV",
      handle: "@LowLevelTV",
      time: "6h",
      text: "setsockopt(SO_REUSEADDR) is one of those things you only learn about after seeing 'Address already in use' for the 10th time.",
      likes: 1204,
      retweets: 445,
      replies: 93,
      liked: false,
      retweeted: false,
    },
    {
      id: 4,
      name: "Julia Evans",
      handle: "@b0rk",
      time: "9h",
      text: "Every time I think I understand file descriptors, I learn something new. Today: sockets are just file descriptors too! Everything is a file.",
      likes: 5621,
      retweets: 1803,
      replies: 241,
      liked: false,
      retweeted: false,
    },
  ],
  nextId: 5,
};

// SVG icons
const icons = {
  reply: `<svg viewBox="0 0 24 24"><path d="M1.751 10c0-4.42 3.584-8 8.005-8h4.366c4.49 0 8.129 3.64 8.129 8.13 0 2.96-1.607 5.68-4.196 7.11l-8.054 4.46v-3.69h-.067c-4.49.1-8.183-3.51-8.183-8.01zm8.005-6c-3.317 0-6.005 2.69-6.005 6 0 3.37 2.77 6.08 6.138 6.01l.351-.01h1.761v2.3l5.087-2.81c1.951-1.08 3.163-3.13 3.163-5.36 0-3.39-2.744-6.13-6.129-6.13H9.756z"/></svg>`,
  retweet: `<svg viewBox="0 0 24 24"><path d="M4.5 3.88l4.432 4.14-1.364 1.46L5.5 7.55V16c0 1.1.896 2 2 2H13v2H7.5c-2.209 0-4-1.79-4-4V7.55L1.432 9.48.068 8.02 4.5 3.88zM16.5 6H11V4h5.5c2.209 0 4 1.79 4 4v8.45l2.068-1.93 1.364 1.46-4.432 4.14-4.432-4.14 1.364-1.46 2.068 1.93V8c0-1.1-.896-2-2-2z"/></svg>`,
  like: `<svg viewBox="0 0 24 24"><path d="M16.697 5.5c-1.222-.06-2.679.51-3.89 2.16l-.805 1.09-.806-1.09C9.984 6.01 8.526 5.44 7.304 5.5c-1.243.07-2.349.78-2.91 1.91-.552 1.12-.633 2.78.479 4.82 1.074 1.97 3.257 4.27 7.129 6.61 3.87-2.34 6.052-4.64 7.126-6.61 1.111-2.04 1.03-3.7.477-4.82-.561-1.13-1.666-1.84-2.908-1.91zm4.187 7.69c-1.351 2.48-4.001 5.12-8.379 7.67l-.503.3-.504-.3c-4.379-2.55-7.029-5.19-8.382-7.67-1.36-2.5-1.41-4.86-.514-6.67.887-1.79 2.647-2.91 4.601-3.01 1.651-.09 3.368.56 4.798 2.01 1.429-1.45 3.146-2.1 4.796-2.01 1.954.1 3.714 1.22 4.601 3.01.896 1.81.846 4.17-.514 6.67z"/></svg>`,
  likedFilled: `<svg viewBox="0 0 24 24"><path d="M20.884 13.19c-1.351 2.48-4.001 5.12-8.379 7.67l-.503.3-.504-.3c-4.379-2.55-7.029-5.19-8.382-7.67-1.36-2.5-1.41-4.86-.514-6.67.887-1.79 2.647-2.91 4.601-3.01 1.651-.09 3.368.56 4.798 2.01 1.429-1.45 3.146-2.1 4.796-2.01 1.954.1 3.714 1.22 4.601 3.01.896 1.81.846 4.17-.514 6.67z"/></svg>`,
};

function formatCount(n) {
  if (n >= 1000) return (n / 1000).toFixed(1).replace(/\.0$/, "") + "K";
  return n.toString();
}

function renderTweet(tweet) {
  const el = document.createElement("article");
  el.className = "tweet";
  el.dataset.id = tweet.id;

  el.innerHTML = `
    <div class="avatar">${tweet.name[0]}</div>
    <div class="tweet-content">
      <div class="tweet-header">
        <span class="tweet-name">${tweet.name}</span>
        <span class="tweet-handle">${tweet.handle}</span>
        <span class="tweet-time">· ${tweet.time}</span>
      </div>
      <div class="tweet-text">${escapeHtml(tweet.text)}</div>
      <div class="tweet-actions">
        <button class="action-btn reply" title="Reply">
          ${icons.reply}
          <span>${formatCount(tweet.replies)}</span>
        </button>
        <button class="action-btn retweet ${tweet.retweeted ? "retweeted" : ""}" title="Retweet">
          ${icons.retweet}
          <span>${formatCount(tweet.retweets)}</span>
        </button>
        <button class="action-btn like ${tweet.liked ? "liked" : ""}" title="Like">
          ${tweet.liked ? icons.likedFilled : icons.like}
          <span>${formatCount(tweet.likes)}</span>
        </button>
      </div>
    </div>
  `;

  el.querySelector(".like").addEventListener("click", (e) => {
    e.stopPropagation();
    toggleLike(tweet.id, el);
  });

  el.querySelector(".retweet").addEventListener("click", (e) => {
    e.stopPropagation();
    toggleRetweet(tweet.id, el);
  });

  return el;
}

function escapeHtml(str) {
  return str
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;");
}

function toggleLike(id, el) {
  const tweet = state.tweets.find((t) => t.id === id);
  if (!tweet) return;

  tweet.liked = !tweet.liked;
  tweet.likes += tweet.liked ? 1 : -1;

  const btn = el.querySelector(".like");
  btn.classList.toggle("liked", tweet.liked);
  btn.querySelector("svg").outerHTML; // replaced below
  btn.innerHTML = `${tweet.liked ? icons.likedFilled : icons.like}<span>${formatCount(tweet.likes)}</span>`;

  btn.addEventListener("click", (e) => {
    e.stopPropagation();
    toggleLike(id, el);
  });
}

function toggleRetweet(id, el) {
  const tweet = state.tweets.find((t) => t.id === id);
  if (!tweet) return;

  tweet.retweeted = !tweet.retweeted;
  tweet.retweets += tweet.retweeted ? 1 : -1;

  const btn = el.querySelector(".retweet");
  btn.classList.toggle("retweeted", tweet.retweeted);
  btn.querySelector("span").textContent = formatCount(tweet.retweets);
}

function renderFeed() {
  const feed = document.getElementById("feed");
  feed.innerHTML = "";
  state.tweets.forEach((tweet) => feed.appendChild(renderTweet(tweet)));
}

function postTweet(text) {
  if (!text.trim()) return;

  const tweet = {
    id: state.nextId++,
    name: "Noel Felix",
    handle: "@noelfelix",
    time: "now",
    text: text.trim(),
    likes: 0,
    retweets: 0,
    replies: 0,
    liked: false,
    retweeted: false,
  };

  state.tweets.unshift(tweet);

  const feed = document.getElementById("feed");
  feed.prepend(renderTweet(tweet));
}

// Wire up compose box
function setupCompose(inputId, btnId, countId) {
  const input = document.getElementById(inputId);
  const btn = document.getElementById(btnId);
  const counter = document.getElementById(countId);

  input.addEventListener("input", () => {
    const remaining = 280 - input.value.length;
    counter.textContent = remaining;
    counter.className = "char-count";
    if (remaining <= 20) counter.classList.add("warning");
    if (remaining < 0) counter.classList.add("danger");
    btn.disabled = input.value.trim().length === 0 || remaining < 0;
  });

  btn.disabled = true;

  btn.addEventListener("click", () => {
    postTweet(input.value);
    input.value = "";
    counter.textContent = "280";
    counter.className = "char-count";
    btn.disabled = true;

    // Close modal if open
    document.getElementById("modal-overlay").classList.remove("open");
  });
}

// Modal
document.getElementById("open-compose").addEventListener("click", () => {
  document.getElementById("modal-overlay").classList.add("open");
  document.getElementById("modal-tweet-input").focus();
});

document.getElementById("modal-close").addEventListener("click", () => {
  document.getElementById("modal-overlay").classList.remove("open");
});

document.getElementById("modal-overlay").addEventListener("click", (e) => {
  if (e.target === e.currentTarget) {
    e.currentTarget.classList.remove("open");
  }
});

// Init
setupCompose("tweet-input", "tweet-btn", "char-count");
setupCompose("modal-tweet-input", "modal-tweet-btn", "modal-char-count");
renderFeed();
