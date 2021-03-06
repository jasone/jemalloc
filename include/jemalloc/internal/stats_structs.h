#ifndef JEMALLOC_INTERNAL_STATS_STRUCTS_H
#define JEMALLOC_INTERNAL_STATS_STRUCTS_H

struct tcache_bin_stats_s {
	/*
	 * Number of allocation requests that corresponded to the size of this
	 * bin.
	 */
	uint64_t	nrequests;
};

struct malloc_bin_stats_s {
	/*
	 * Total number of allocation/deallocation requests served directly by
	 * the bin.  Note that tcache may allocate an object, then recycle it
	 * many times, resulting many increments to nrequests, but only one
	 * each to nmalloc and ndalloc.
	 */
	uint64_t	nmalloc;
	uint64_t	ndalloc;

	/*
	 * Number of allocation requests that correspond to the size of this
	 * bin.  This includes requests served by tcache, though tcache only
	 * periodically merges into this counter.
	 */
	uint64_t	nrequests;

	/*
	 * Current number of regions of this size class, including regions
	 * currently cached by tcache.
	 */
	size_t		curregs;

	/* Number of tcache fills from this bin. */
	uint64_t	nfills;

	/* Number of tcache flushes to this bin. */
	uint64_t	nflushes;

	/* Total number of slabs created for this bin's size class. */
	uint64_t	nslabs;

	/*
	 * Total number of slabs reused by extracting them from the slabs heap
	 * for this bin's size class.
	 */
	uint64_t	reslabs;

	/* Current number of slabs in this bin. */
	size_t		curslabs;
};

struct malloc_large_stats_s {
	/*
	 * Total number of allocation/deallocation requests served directly by
	 * the arena.
	 */
	uint64_t	nmalloc;
	uint64_t	ndalloc;

	/*
	 * Number of allocation requests that correspond to this size class.
	 * This includes requests served by tcache, though tcache only
	 * periodically merges into this counter.
	 */
	uint64_t	nrequests;

	/* Current number of allocations of this size class. */
	size_t		curlextents;
};

struct arena_stats_s {
	/* Number of bytes currently mapped. */
	size_t		mapped;

	/*
	 * Number of bytes currently retained as a side effect of munmap() being
	 * disabled/bypassed.  Retained bytes are technically mapped (though
	 * always decommitted or purged), but they are excluded from the mapped
	 * statistic (above).
	 */
	size_t		retained;

	/*
	 * Total number of purge sweeps, total number of madvise calls made,
	 * and total pages purged in order to keep dirty unused memory under
	 * control.
	 */
	uint64_t	npurge;
	uint64_t	nmadvise;
	uint64_t	purged;

	size_t		base;
	size_t		internal; /* Protected via atomic_*_zu(). */
	size_t		resident;

	size_t		allocated_large;
	uint64_t	nmalloc_large;
	uint64_t	ndalloc_large;
	uint64_t	nrequests_large;

	/* One element for each large size class. */
	malloc_large_stats_t	lstats[NSIZES - NBINS];
};

#endif /* JEMALLOC_INTERNAL_STATS_STRUCTS_H */
